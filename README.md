# DS-online-shoppping-MS
📦 **Integrated Inventory Management System (C++)**

A lightweight inventory and supplier management system built using C++ and core data structures such as Linked Lists, Stacks, Queues, and Binary Search Trees (BSTs).
Designed for store or factory owners to efficiently organize spare parts, suppliers, and their relationships.

**🚀 Features**

- Manage Spare Parts (add, modify, display, search)
- 
- Manage Suppliers (add, modify, display, search)
- 
- Link each spare part to its list of suppliers
- 
- Maintain interaction history using a Stack
- 
- Process updates and operations using Queues
- 
- Fast searching and deletion through BST-based indexing
- 
- Ensures unique identifiers (part numbers & supplier codes)

**🧱 Data Structures Used**

- **Linked Lists** → store suppliers for each spare part & vice versa
- 
- **Stacks** → log user interactions (last-in, first-out)
- 
- **Queues** → process part/supplier updates
- 
- **Binary Search Trees (BSTs)** → efficient search & delete operations
- 
- **Classes & OOP** → structure for SparePart and Supplier

**🖥️ How It Works**

- User can add up to 100 spare parts and 20 suppliers
- 
- Every part/supplier is stored in a BST for quick lookup
- 
- Relationships are maintained using linked lists
- 
- Input actions are tracked in a stack
- 
- All processing steps are queued for sequential execution
- 
- System displays organized inventory and supplier data


🧪 **Example Functionalities**

- Add new spare part
- 
- Add supplier to a part
- 
- Modify part/supplier data
- 
- Search by part number or supplier code
- 
- View linked suppliers per part
- 
- Display entire inventory
- 
- View interaction history (stack)
- 
- Process update queue
