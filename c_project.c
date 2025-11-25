#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item_node{
    char name[20];
    int quantity;
    float price;
    struct item_node *next;
};

struct category_node{
    char name[20];
    int variety;
    struct item_node* item_head;
};

struct shopkeeper{
    char name[20];
    int age;
    char address[50];
    int category_variety;
    struct category_node list[1000];
};

struct item_node * create_item_node(char* name, int quantity, float price){
    struct item_node* new_node = malloc(sizeof(struct item_node));
    strcpy(new_node->name, name);
    new_node->quantity = quantity;
    new_node->price = price;                                                                                                                                                                            new_node->next = NULL;
    return new_node;
}

void append_item_node(struct item_node* head, char* name, int quantity, float price){
    struct item_node* new_node = create_item_node(name, quantity, price);
    if(head == NULL){
        head = new_node;
        return;
    }
    struct item_node* temp = head;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = new_node;
}

struct item_node* get_item(struct item_node* head, char name[]){
    struct item_node* temp = head;
    while(temp != NULL){
        if(strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void create_innventory(struct shopkeeper* shop){
    printf("Enter shopkeeper name: ");
    scanf(" %s", shop->name);
    printf("Enter age: ");                                                                                                                                                                                      scanf("%d", &shop->age);
    printf("Enter address: ");
    scanf(" %s", shop->address);

    printf("Enter number of categories: ");
    scanf("%d", &shop->category_variety);

    //shop->list = malloc(shop->category_variety * sizeof(struct category_node));

    for(int i=0; i<shop->category_variety; i++){
        printf("Enter category %d name: ", i+1);
        scanf(" %s", shop->list[i].name);

        printf("Enter number of items in %s: ", shop->list[i].name);
        scanf("%d", &shop->list[i].variety);

        shop->list[i].item_head = NULL;

        for(int j=0; j<shop->list[i].variety; j++){
            char item_name[20];
            int quantity;
            float price;

            printf("Enter item %d name: ", j+1);
            scanf(" %s", item_name);

            printf("Enter quantity of %s: ", item_name);
            scanf("%d", &quantity);

            printf("Enter price of %s: ", item_name);                                                                                                                              scanf("%f", &price);

            if(shop->list[i].item_head == NULL){
                shop->list[i].item_head = create_item_node(item_name, quantity, price);
            } else {
                append_item_node(shop->list[i].item_head, item_name, quantity, price);
            }
        }
    }
}

void add_item_to_category(struct category_node* cat, char* name, int quantity, float price){
    struct item_node* new_node = create_item_node(name, quantity, price);

    if(cat->item_head == NULL){
        cat->item_head = new_node;
    } else {
        struct item_node* temp = cat->item_head;
        while(temp->next != NULL) temp = temp->next;
        temp->next = new_node;
    }
    cat->variety += 1;
}

void add_to_inventory(struct shopkeeper* shop){
    if(shop->list == NULL){
        printf("No inventory exists. Create inventory first.\n");
        return;
    }                                                                                                                                                                                                        char category_name[20];
    printf("\nEnter Category name: ");
    scanf(" %s", category_name);

    int idx = -1;
    for(int i=0; i<shop->category_variety; i++){
        if(strcmp(category_name, shop->list[i].name) == 0){
            idx = i;
            break;
        }
    }

    char item_name[20];
    int qty;
    float price;

    printf("Enter Item name: ");
    scanf(" %s", item_name);
    printf("Enter Quantity: ");
    scanf("%d", &qty);
    printf("Enter Price: ");
    scanf("%f", &price);

    if(idx != -1){
        struct item_node* item = get_item(shop->list[idx].item_head, item_name);
        if(item != NULL){
            item->quantity += qty;
            item->price = price;
            printf("\nUpdated item %s.\n", item_name);
        } else {                                                                                                                                                                                           add_item_to_category(&shop->list[idx], item_name, qty, price);
            printf("\nAdded new item %s.\n", item_name);
        }
    } else {
        printf("\nCreating new category %s.\n", category_name);

        //shop->list = realloc(shop->list, (shop->category_variety+1)*sizeof(struct category_node));

        int new_idx = shop->category_variety;
        shop->category_variety++;

        strcpy(shop->list[new_idx].name, category_name);
        shop->list[new_idx].variety = 0;
        shop->list[new_idx].item_head = NULL;

        add_item_to_category(&shop->list[new_idx], item_name, qty, price);
    }
}

void displayInventory(struct shopkeeper* shop){
    printf("\n--- INVENTORY ---\n");
    for(int i=0; i<shop->category_variety; i++){
        printf("\nCategory: %s\n", shop->list[i].name);
        struct item_node* temp = shop->list[i].item_head;
        while(temp != NULL){
            printf("Item: %s | Qty: %d | Price: %f\n",
                   temp->name, temp->quantity, temp->price);
            temp = temp->next;
        }
    }               
}
void update_item(struct shopkeeper* shop){
    char category_name[20],item_name[20];
    int quantity;
    float price;
    printf("\nEnter catgory in which item is present: ");
    scanf(" %s",category_name);
    printf("Enter item for which details have to be changed: ");
    scanf(" %s",item_name);
    printf("Enter the new quantity for %s: ",item_name);
    scanf("%d",&quantity);
    printf("Enter the new price for %s: ",item_name);
    scanf("%f",&price);
    for(int i=0;i<shop->category_variety;i++){
        if(strcmp(category_name,shop->list[i].name)==0){
             struct item_node* item=get_item(shop->list[i].item_head,item_name);
             if(item == NULL){
                 printf("Item not found.\n");
                 return;
            }
            item->quantity=quantity;
            item->price=price;
            return;
        }

   }
 }

void delete_item(struct shopkeeper* shop){
    char category_name[20], item_name[20];
    printf("\nEnter Category name: ");
    scanf(" %s", category_name);
    printf("Enter Item name to delete: ");
    scanf(" %s", item_name);

    for(int i=0; i<shop->category_variety; i++){
        if(strcmp(category_name, shop->list[i].name) == 0){
            struct item_node* temp = shop->list[i].item_head;
            struct item_node* prev = NULL;

            while(temp != NULL){
                if(strcmp(temp->name, item_name) == 0){
                    if(prev == NULL){
                        shop->list[i].item_head = temp->next;
                    } else {
                        prev->next = temp->next;
                    }
                    free(temp);
                    shop->list[i].variety -= 1;
                    printf("Item deleted.\n");
                    return;
                }
                prev = temp;
                temp = temp->next;
            }
            printf("Item not found in category.\n");
            return;
        }
    }
    printf("Category not found.\n");
}

void search_item(struct shopkeeper* shop){
    char item_name[20];
    printf("\nEnter Item name to search: ");
    scanf(" %s", item_name);

    for(int i=0; i<shop->category_variety; i++){
        struct item_node* temp = shop->list[i].item_head;
        while(temp != NULL){
            if(strcmp(temp->name, item_name) == 0){
                printf("Found in Category: %s | Qty: %d | Price: %f\n",
                       shop->list[i].name, temp->quantity, temp->price);
                return;
            }
            temp = temp->next;
        }
    }
    printf("Item not found in inventory.\n");
}

void sell_item(struct shopkeeper* shop){
    char category_name[20], item_name[20];                                                                                                                                  int qtyToSell;

    printf("\nEnter Category: ");
    scanf(" %s", category_name);
    printf("Enter Item: ");
    scanf(" %s", item_name);
    printf("Enter Quantity: ");
    scanf("%d", &qtyToSell);

    for(int i=0; i<shop->category_variety; i++){
        if(strcmp(category_name, shop->list[i].name) == 0){

            struct item_node* item = get_item(shop->list[i].item_head, item_name);
            if(item == NULL){
                printf("Item not found.\n");
                return;
            }
            if(qtyToSell > item->quantity){
                printf("Not enough stock.\n");
            } else {
                item->quantity -= qtyToSell;
                printf("Sold.\n Remaining: %d\n", item->quantity);
            }
            return;
        }
    }
    printf("Category not found.\n");
}

void save_to_file(struct shopkeeper* shop){                                                                                                                                 FILE* fp = fopen("inventory.txt", "w");
    fprintf(fp, "%s\n%d\n%s\n", shop->name, shop->age, shop->address);

    fprintf(fp, "%d\n", shop->category_variety);

    for(int i=0; i<shop->category_variety; i++){
        fprintf(fp, "%s\n%d\n", shop->list[i].name, shop->list[i].variety);

        struct item_node* temp = shop->list[i].item_head;
        while(temp != NULL){
            fprintf(fp, "%s %d %f\n", temp->name, temp->quantity, temp->price);
            temp = temp->next;
        }
    }

    fclose(fp);
    printf("Inventory saved.\n");
}

void load(struct shopkeeper* shop){
    FILE* fp = fopen("inventory.txt", "r");
    if(!fp){
        printf("File not found.\n");
        return;
    }

    fscanf(fp, " %s", shop->name);
    fscanf(fp, "%d", &shop->age);
    fscanf(fp, " %s", shop->address);
    fscanf(fp, "%d", &shop->category_variety);    

    for(int i=0; i<shop->category_variety; i++){
        fscanf(fp, " %s", shop->list[i].name);
        fscanf(fp, "%d", &shop->list[i].variety);

        shop->list[i].item_head = NULL;

        for(int j=0; j<shop->list[i].variety; j++){
            char item_name[20];
            int quantity;
            float price;

            fscanf(fp, "%s %d %f", item_name, &quantity, &price);

            if(shop->list[i].item_head == NULL){
                shop->list[i].item_head = create_item_node(item_name, quantity, price);
            }else {
                append_item_node(shop->list[i].item_head, item_name, quantity, price);
            }
        }
    }

    fclose(fp);
    printf("Inventory loaded.\n");
}

void free_inventory(struct shopkeeper* shop){
    for(int i=0; i<shop->category_variety; i++){
        struct item_node* temp = shop->list[i].item_head;
        while(temp != NULL){
            struct item_node* to_free = temp;
            temp = temp->next;
            free(to_free);
        }
    }
    //free(shop->list);
    free(shop);
}

int main(){
    struct shopkeeper *shop = malloc(sizeof(struct shopkeeper));                                      
    int option, created = 0;

    while(1){
        printf("\n--- SHOP MENU ---\n");
        printf("1. Create Inventory\n");
        printf("2. Display Inventory\n");
        printf("3. Sell Item\n");
        printf("4. Save Inventory\n");
        printf("5. Load Inventory\n");
        printf("6. Add to Inventory\n");
        printf("7. Update item\n");
        printf("8 . Delete Item\n");
        printf("9. Search Item\n");
        printf("10. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &option);

        switch(option){
            case 1: if(!created){ create_innventory(shop); created=1; } else printf("Already created.\n"); break;
            case 2: displayInventory(shop); break;
            case 3: sell_item(shop); break;
            case 4: save_to_file(shop); break;
            case 5: load(shop); break;
            case 6: add_to_inventory(shop); break;
            case 7: update_item(shop);break;
            case 8: delete_item(shop);break;
            case 9: search_item(shop); break;
            case 10: return 0;
            default: printf("Invalid.\n");
        }
    }
    free_inventory(shop);
    return 0;
}                                                                                                                                                                      
