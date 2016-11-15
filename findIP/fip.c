/**********************************************************************************
HARMAN BASIC CONNECTIVITY ANALYTICS
Kevin Hague, Harman International
June 4th, 2016

COLLECTS:
*** MAC ADDRESS
*** IPADDRESS
*** mS Latency to Harman Cloud (RESPONSE FOR POST)
*** Wi-Fi(if enabled) Signal Strength, Channel, Freq, MCS Rate

TODO:
MAC ADDRESS (client and endpoint code needed)
mS Latency (endpoint needed)
Wi-Fi Stuff
**********************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>

int main (int argc, const char * argv[]) {
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;
	int curlInit=0;
	CURL *curl;
	CURLcode res;
	char urlString[500]; //temporary URL string
	
	char hostname[1024];  //system hostname


    struct timeval start, end;

    long mtime, seconds, useconds;    

    gethostname(hostname, 1024);
    printf("\nHostname: %s\n", hostname);

    gettimeofday(&start, NULL);
 //   usleep(2000);



	/*initialize CURL Session.  This currently does not need SSL.  Use CURL_GLOBAL_SSL when init to enable SSL*/
	curlInit = curl_global_init(CURL_GLOBAL_NOTHING);
	if(curlInit==0) {
    	curl = curl_easy_init();
	} else {
		printf("Unable to start CURL\n\n");
		return 0;
	}

	//get IP Adddresses
    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
			if(strncmp( "lo", ifa->ifa_name, 2) != 0) {
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            printf("\n\n%s IP Address %s :\n\n", ifa->ifa_name, addressBuffer); 
			sprintf(urlString,"http://hkiotcloud.azurewebsites.net/internal/postIPInfo?name=%s-%s&ip=%s", hostname, ifa->ifa_name, addressBuffer);
			printf("%s", urlString);
			  if(curl) {
    			  curl_easy_setopt(curl, CURLOPT_URL, urlString);

			    /* Perform the request, res will get the return code */ 
			    res = curl_easy_perform(curl);
			    /* Check for errors */ 
			    if(res != CURLE_OK) {
			      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
				} else {
					printf("%s",res);
					printf("\n\n");
				}
			
			  }
			sprintf(urlString, "");
			}
        } 
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);

    if(curlInit) {
    	curl_easy_cleanup(curl);
    	curl_global_cleanup();
    }
	printf("\n\n");

    gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %ld milliseconds\n", mtime);

    return 0;
}
