#include <stdio.h>

void start_sniffer();
void open_door();
void close_door();

int main() {
 int option;
    do {
        printf("\n\t === NetTool C ===\n\n");
        printf("\t1. Start sniffer\n");
        printf("\t2. Open TCP port\n");
        printf("\t3. Close TCP port\n");
        printf("\t4. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1: start_sniffer(); break;
            case 2: open_door(); break;
            case 3: close_door(); break;
            case 0: printf("Bye!\n"); break;
            default: printf("Invalid option!\n"); break;
        }
    } while (option != 0);
    return 0;
}