#include <stdio.h>

#define MAX_P 10

int main() {
	int i,j;
    int reference_string[MAX_P];
    int frames[MAX_P];
    int no_of_frames, no_of_pages, page_faults = 0, page_hits = 0;
    int frame_index = 0, reference_index = 0;

    printf("Enter the number of frames: ");
    scanf("%d", &no_of_frames);

    printf("Enter the reference string (space-separated): ");
    for (i = 0; i < MAX_P; i++) {
        reference_string[i] = -1;
        frames[i] = -1;
    }

    no_of_pages = 0;
    while (no_of_pages < MAX_P && scanf("%d", &reference_string[no_of_pages]) == 1) {
        no_of_pages++;
    }

    printf("\nReference String: ");
    for (i = 0; i < no_of_pages; i++) {
        printf("%d ", reference_string[i]);
    }

    printf("\n\n");

    printf("Reference String\tPage Frames\n");

    for (i = 0; i < no_of_pages; i++) {
        int page = reference_string[i];
        int found = 0;

        printf("%d\t\t\t", page);

        for (j = 0; j < no_of_frames; j++) {
            if (frames[j] == page) {
                found = 1;
                page_hits++;
                break;
            }
        }

        if (!found) {
            frames[frame_index] = page;
            frame_index = (frame_index + 1) % no_of_frames;
            page_faults++;
            printf("+ ");
        } else {
            printf("* ");
        }

        for (j = 0; j < no_of_frames; j++) {
            if (frames[j] == -1) {
                printf("- ");
            } else {
                printf("%d ", frames[j]);
            }
        }

        printf("\n");
    }

    double hit_ratio = (double) page_hits / (page_faults + page_hits);

    printf("\nPage Faults: %d\n", page_faults);
    printf("Page Hits: %d\n", page_hits);
    printf("Hit Ratio: %.2lf\n", hit_ratio);

    return 0;
}
