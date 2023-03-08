#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

char **download_feed_files(void);
void download_files_from_feeds(char **feed_files);

int main(void)
{
    char **returned_filenames = download_feed_files();
    for (int i = 0; i < 2; ++i)
    {
        printf("%s\n", returned_filenames[i]);
    }

    download_files_from_feeds(returned_filenames);

    // Free the memory allocated for the array of strings
    for (int i = 0; i < 2; ++i)
    {
        free(returned_filenames[i]);
    }
    free(returned_filenames);

    return 0;
}

char **download_feed_files(void)
{
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *feeds[] = {
        "http://data.gdeltproject.org/gdeltv2/lastupdate.txt",
        "http://data.gdeltproject.org/gdeltv2/lastupdate-translation.txt"};
    char *file_names[] = {
        "lastupdate.txt",
        "lastupdate-translation.txt"};

    // Allocate memory for an array of pointers to strings
    char **returned_filenames = malloc(sizeof(char *) * 2);

    for (int i = 0; i < 2; ++i)
    {
        curl = curl_easy_init();
        if (curl)
        {
            fp = fopen(file_names[i], "wb");
            curl_easy_setopt(curl, CURLOPT_URL, feeds[i]);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            fclose(fp);

            // Allocate memory for the filename string and copy it
            returned_filenames[i] = malloc(sizeof(char) * (strlen(file_names[i]) + 1));
            strcpy(returned_filenames[i], file_names[i]);
        }
    }

    return returned_filenames;
}

void download_files_from_feeds(char **feed_files)
{
    for (int i = 0; i < 2; ++i)
    {
        printf("%s\n", feed_files[i]);
    }
}