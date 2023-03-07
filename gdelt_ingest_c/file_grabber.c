#include <stdio.h>
#include <curl/curl.h>

int main(void)
{
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *feeds[] = { 
        "http://data.gdeltproject.org/gdeltv2/lastupdate.txt", 
        "http://data.gdeltproject.org/gdeltv2/lastupdate-translation.txt"  
        };
    char *file_names[] = {
        "lastupdate.txt",
        "lastupdate-translation.txt"
    };

    curl = curl_easy_init();

    for ( int i = 0; i < 2; ++i)
    {
        fp = fopen(file_names[i], "wb");
        curl_easy_setopt(curl, CURLOPT_URL, feeds[i]);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }

    return 0;
}