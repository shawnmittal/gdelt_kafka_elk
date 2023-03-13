#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

char **download_feed_files(void);
int download_file_from_url(char *filename, char *url);
char **download_files_from_feeds(char **feed_files);

int main(void)
{
    char **returned_filenames = download_feed_files();
    for (int i = 0; i < 2; ++i)
    {
        printf("%s\n", returned_filenames[i]);
    }

    download_files_from_feeds(returned_filenames);

    // Delete the downloaded files
    for (int i = 0; i < 2; ++i)
    {
        remove(returned_filenames[i]);
    }

    // Free the memory allocated for the array of strings
    for (int i = 0; i < 2; ++i)
    {
        free(returned_filenames[i]);
    }
    free(returned_filenames);

    return 0;
}

int download_file_from_url(char *filename, char *url)
{
    CURL *curl;
    FILE *file;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        file = fopen(filename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(file);

        return 0;
    }
    return 1;
}

char **download_feed_files(void)
{
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *feeds[] = {
        "http://data.gdeltproject.org/gdeltv2/lastupdate.txt",
        "http://data.gdeltproject.org/gdeltv2/lastupdate-translation.txt"};
    char *filenames[] = {
        "lastupdate.txt",
        "lastupdate-translation.txt"};

    // Allocate memory for an array of pointers to strings
    char **returned_filenames = malloc(sizeof(char *) * 2);

    for (int i = 0; i < 2; ++i)
    {
        download_file_from_url(filenames[i], feeds[i]);

        // Allocate memory for the filename string and copy it
        returned_filenames[i] = malloc(sizeof(char) * (strlen(filenames[i]) + 1));
        strcpy(returned_filenames[i], filenames[i]);
    }

    return returned_filenames;
}

char **download_files_from_feeds(char **feed_files)
{
    FILE *fp;
    char line[200];
    int file_counter = 0;

    for (int i = 0; i < 2; ++i)
    {
        fp = fopen(feed_files[i], "r");

        if (fp == NULL)
        {
            printf("Unable to open file.\n");
        }

        while (fgets(line, sizeof(line), fp) != NULL)
        {
            char *token = strtok(line, " ");

            while (token != NULL)
            {
                if (strncmp(token, "http://data.gdeltproject.org", 28) == 0)
                {
                    // Remove newline character from last token
                    token[strcspn(token, "\n")] = 0;

                    // Extract the filename from the url
                    char chunk[200];
                    strcpy(chunk, token);
                    // printf("%s\n", token);
                    char *filename;
                    filename = strrchr(chunk, '/');
                    filename++;
                    printf("%s\n", filename);
                    file_counter++;

                    download_file_from_url(filename, token);
                }
                token = strtok(NULL, " ");
            }
        }
        fclose(fp);
    }

    return 0;
}