# C_Project
Shop Inventory System

Overview: - 
This project hels a shopkeeper to maintain his various items in his inventory.
This will help him in keeping a track of his stock. This program stores info about the category of item and item name, quantity and price. It can display all the itmes shopkeeper has and he can update, delete and search and sell items. He can also save the data in a file and load it in the next run of the code.

Features :-
i) Create inventory with multiple categories and items
ii) Display the entire inventory with categories and their items
iii) Add new items to existing or new categories
iv) Update quantity and price of existing items
v) Delete items from a user specified category 
vi) It updates the stock after selling item
vii) Save inventory to a text file (inventory.txt)
viii) Load inventory from the same file
ix) Proper memory management with dynamic allocation for linked list items       and an array for categories

Code Structure:- 
a) struct item_node: Represents individual items in a category using a linked list
b) struct category_node: Represents categories containing a linked list of items
c) struct shopkeeper: Represents the shopkeeper and holds categories in a fixed-size array
d) Functions to create, add, update, delete, search, sell, save, load items/inventory
e) Uses dynamic memory allocation (malloc) for item nodes
f) Uses file I/O to persist inventory between runs

How to use: - 
i) Compile the code
ii) Run the executable
iii) Use the menu to interact by various options (1 - 10)

Notes:- 
This program uses static array for storing array for categories. Items are dynamically allocated linked lists . Memoery is freed upon program exit for dynamically created nodes. The inventory is saved in a simple text format in 'inventory.txt'. Input is straightforward string and numeric input via scanf.

Contributions:-
Sanchit Gupta - save_file, update_item, free_inventory, append_item_node, thought of all the various features
Soumya Gupta - load_file, create_item_node, create_innvemtory, add_to_inventory, delete item, sell_item
Yatharth Prakul Shrotriya - get_item, search_item, display_inventory, readme file





