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
#include <stdlib.h>

int main (int argc, const char * argv[]) {
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;
	int curlInit=0;
	CURL *curl;
	CURLcode res;
	char urlString[500];

    char hostname[1024];


    struct timeval start, end;

    long mtime, seconds, useconds;    

    if (argc < 2) {
        printf("Usage: SendLatency service_name latency_time\n");
        printf(" for example: SendLatency IBM 3.123\n");
        exit(0);
    }
    
    gethostname(hostname, 1024);
    printf("\nhostname: %s\n", hostname);

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


    sprintf(urlString,"http://hkiotcloud.azurewebsites.net/internal/postLatency?name=%s&service=%s&latency=%s", hostname, argv[1], argv[2]);
    printf("%s\n", urlString);
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


    if(curlInit) {
    	curl_easy_cleanup(curl);
    	curl_global_cleanup();
    }
	printf("\n\n");


    return 0;
}
