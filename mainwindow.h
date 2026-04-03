// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>

// Include ALL your existing classes here
#include <string>
#include <sstream>
using namespace std;

// Copy ALL your class definitions from your original code
// (Supplier, SparePart, SupplierLink, PartLink, StackNode, QueueNode, etc.)

class Supplier;
class SparePart;

struct SupplierLink {
    Supplier* supplier;
    SupplierLink* next;
    SupplierLink(Supplier* sup) : supplier(sup), next(nullptr) {}
};

struct PartLink {
    SparePart* part;
    PartLink* next;
    PartLink(SparePart* p) : part(p), next(nullptr) {}
};

struct StackNode {
    string message;
    StackNode* next;
    StackNode(const string& msg) : message(msg), next(nullptr) {}
};

struct QueueNode {
    string message;
    QueueNode* next;
    QueueNode(const string& msg) : message(msg), next(nullptr) {}
};

class InteractionStack {
    StackNode* topNode;
public:
    InteractionStack() : topNode(nullptr) {}
    ~InteractionStack() {
        while (topNode) {
            StackNode* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }
    void push(const string& msg) {
        StackNode* node = new StackNode(msg);
        node->next = topNode;
        topNode = node;
    }
    string getDisplay() const {
        stringstream ss;
        const StackNode* current = topNode;
        ss << "--- Interaction History (Most Recent First) ---\n\n";
        int count = 1;
        while (current) {
            ss << count++ << ". " << current->message << "\n";
            current = current->next;
        }
        if (!topNode) {
            ss << "No interactions yet.\n";
        }
        return ss.str();
    }
};

class ProcessingQueue {
    QueueNode* frontNode;
    QueueNode* rearNode;
public:
    ProcessingQueue() : frontNode(nullptr), rearNode(nullptr) {}
    ~ProcessingQueue() {
        while (frontNode) {
            QueueNode* temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
        }
    }
    void enqueue(const string& msg) {
        QueueNode* node = new QueueNode(msg);
        if (!rearNode) {
            frontNode = rearNode = node;
        } else {
            rearNode->next = node;
            rearNode = node;
        }
    }
    string getDisplay() const {
        stringstream ss;
        ss << "--- Pending Processing Queue (Oldest First) ---\n\n";
        const QueueNode* current = frontNode;
        int count = 1;
        while (current) {
            ss << count++ << ". " << current->message << "\n";
            current = current->next;
        }
        if (!frontNode) {
            ss << "No pending updates.\n";
        }
        return ss.str();
    }
};

class SparePart {
    string partName;
    int partNumber;
    double cost;
    int existingParts;
    SupplierLink* supplierHead;
public:
    SparePart() : partName(""), partNumber(0), cost(0.0), existingParts(0), supplierHead(nullptr) {}
    int getPartNumber() const { return partNumber; }
    void setPartNumber(int number) { partNumber = number; }
    const string& getPartName() const { return partName; }
    void setPartName(const string& name) { partName = name; }
    void setCost(double c) { cost = c; }
    void setExistingParts(int count) { existingParts = count; }
    double getCost() const { return cost; }
    int getExistingParts() const { return existingParts; }

    void addSupplierLink(Supplier* supplier);
    bool isLinkedToSupplier(int supplierCode) const;
    string getSuppliersList() const;
};

class Supplier {
    string supplierName;
    int supplierCode;
    string address;
    string telephone;
    string email;
    PartLink* partHead;
public:
    Supplier() : supplierName(""), supplierCode(0), address(""), telephone(""), email(""), partHead(nullptr) {}
    int getSupplierCode() const { return supplierCode; }
    const string& getSupplierName() const { return supplierName; }
    void setSupplierCode(int code) { supplierCode = code; }
    void setSupplierName(const string& name) { supplierName = name; }
    void setAddress(const string& addr) { address = addr; }
    void setTelephone(const string& tel) { telephone = tel; }
    void setEmail(const string& em) { email = em; }
    const string& getAddress() const { return address; }
    const string& getTelephone() const { return telephone; }
    const string& getEmail() const { return email; }

    void addPartLink(SparePart* part) {
        if (isLinkedToPart(part->getPartNumber())) return;
        PartLink* node = new PartLink(part);
        node->next = partHead;
        partHead = node;
    }

    bool isLinkedToPart(int partNumber) const {
        PartLink* current = partHead;
        while (current) {
            if (current->part->getPartNumber() == partNumber) return true;
            current = current->next;
        }
        return false;
    }

    string getPartsList() const;
};

inline void SparePart::addSupplierLink(Supplier* supplier) {
    if (isLinkedToSupplier(supplier->getSupplierCode())) return;
    SupplierLink* node = new SupplierLink(supplier);
    node->next = supplierHead;
    supplierHead = node;
}

inline bool SparePart::isLinkedToSupplier(int supplierCode) const {
    SupplierLink* current = supplierHead;
    while (current) {
        if (current->supplier->getSupplierCode() == supplierCode) return true;
        current = current->next;
    }
    return false;
}

inline string SparePart::getSuppliersList() const {
    stringstream ss;
    SupplierLink* current = supplierHead;
    if (current) {
        ss << "Suppliers: ";
        while (current) {
            ss << current->supplier->getSupplierCode() << " ("
               << current->supplier->getSupplierName() << ") ";
            current = current->next;
        }
    } else {
        ss << "No suppliers linked";
    }
    return ss.str();
}

inline string Supplier::getPartsList() const {
    stringstream ss;
    PartLink* current = partHead;
    if (current) {
        ss << "Parts: ";
        while (current) {
            ss << current->part->getPartNumber() << " ("
               << current->part->getPartName() << ") ";
            current = current->next;
        }
    } else {
        ss << "No parts linked";
    }
    return ss.str();
}

// Copy your BST classes
class SparePartBST {
    struct Node {
        SparePart data;
        Node* left;
        Node* right;
        Node(const SparePart& part) : data(part), left(nullptr), right(nullptr) {}
    };
    Node* root;
    int count;
    const int MAX_PARTS = 100;

    Node* insert(Node* node, const SparePart& part, bool& inserted) {
        if (!node) {
            inserted = true;
            return new Node(part);
        }
        if (part.getPartNumber() < node->data.getPartNumber()) {
            node->left = insert(node->left, part, inserted);
        } else if (part.getPartNumber() > node->data.getPartNumber()) {
            node->right = insert(node->right, part, inserted);
        } else {
            inserted = false;
        }
        return node;
    }

    Node* search(Node* node, int partNumber) const {
        if (!node || node->data.getPartNumber() == partNumber) return node;
        if (partNumber < node->data.getPartNumber()) {
            return search(node->left, partNumber);
        }
        return search(node->right, partNumber);
    }

    void inorder(Node* node, stringstream& ss) const {
        if (!node) return;
        inorder(node->left, ss);
        ss << node->data.getPartNumber() << " | "
           << node->data.getPartName() << " | $"
           << node->data.getCost() << " | "
           << node->data.getExistingParts() << "\n  "
           << node->data.getSuppliersList() << "\n\n";
        inorder(node->right, ss);
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    SparePartBST() : root(nullptr), count(0) {}
    ~SparePartBST() { destroy(root); }

    bool insert(const SparePart& part) {
        if (count >= MAX_PARTS) return false;
        bool inserted = false;
        root = insert(root, part, inserted);
        if (inserted) ++count;
        return inserted;
    }

    SparePart* search(int partNumber) const {
        Node* node = search(root, partNumber);
        if (node) return &node->data;
        return nullptr;
    }

    string displayAll() const {
        stringstream ss;
        ss << "=== ALL SPARE PARTS ===\n\n";
        ss << "Part# | Name | Cost | Qty\n";
        ss << string(60, '-') << "\n\n";
        inorder(root, ss);
        ss << "Total Parts: " << count << "\n";
        return ss.str();
    }

    int size() const { return count; }
};

class SupplierBST {
    struct Node {
        Supplier data;
        Node* left;
        Node* right;
        Node(const Supplier& sup) : data(sup), left(nullptr), right(nullptr) {}
    };
    Node* root;
    int count;
    const int MAX_SUPPLIERS = 20;

    Node* insert(Node* node, const Supplier& sup, bool& inserted) {
        if (!node) {
            inserted = true;
            return new Node(sup);
        }
        if (sup.getSupplierCode() < node->data.getSupplierCode()) {
            node->left = insert(node->left, sup, inserted);
        } else if (sup.getSupplierCode() > node->data.getSupplierCode()) {
            node->right = insert(node->right, sup, inserted);
        } else {
            inserted = false;
        }
        return node;
    }

    Node* search(Node* node, int supplierCode) const {
        if (!node || node->data.getSupplierCode() == supplierCode) return node;
        if (supplierCode < node->data.getSupplierCode()) {
            return search(node->left, supplierCode);
        }
        return search(node->right, supplierCode);
    }

    void inorder(Node* node, stringstream& ss) const {
        if (!node) return;
        inorder(node->left, ss);
        ss << node->data.getSupplierCode() << " | "
           << node->data.getSupplierName() << " | "
           << node->data.getTelephone() << " | "
           << node->data.getEmail() << "\n  "
           << node->data.getPartsList() << "\n\n";
        inorder(node->right, ss);
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    SupplierBST() : root(nullptr), count(0) {}
    ~SupplierBST() { destroy(root); }

    bool insert(const Supplier& sup) {
        if (count >= MAX_SUPPLIERS) return false;
        bool inserted = false;
        root = insert(root, sup, inserted);
        if (inserted) ++count;
        return inserted;
    }

    Supplier* search(int supplierCode) const {
        Node* node = search(root, supplierCode);
        if (node) return &node->data;
        return nullptr;
    }

    string displayAll() const {
        stringstream ss;
        ss << "=== ALL SUPPLIERS ===\n\n";
        ss << "Code | Name | Phone | Email\n";
        ss << string(70, '-') << "\n\n";
        inorder(root, ss);
        ss << "Total Suppliers: " << count << "\n";
        return ss.str();
    }

    int size() const { return count; }
};

inline void linkPartAndSupplier(SparePart* part, Supplier* supplier) {
    if (!part || !supplier) return;
    part->addSupplierLink(supplier);
    supplier->addPartLink(part);
}

// MainWindow class
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddSparePart();
    void onAddSupplier();
    void onSearchSparePart();
    void onSearchSupplier();
    void onModifyRecord();
    void onDisplayAllParts();
    void onDisplayAllSuppliers();
    void onShowHistory();
    void onShowQueue();
    void onLinkSupplierToPart();

private:
    QWidget *centralWidget;
    QTextEdit *displayText;
    QPushButton *btnAddPart, *btnAddSupplier, *btnSearchPart, *btnSearchSupplier;
    QPushButton *btnModify, *btnDisplayParts, *btnDisplaySuppliers;
    QPushButton *btnHistory, *btnQueue, *btnLink;

    // Your existing data structures
    SparePartBST partTree;
    SupplierBST supplierTree;
    InteractionStack historyStack;
    ProcessingQueue processQueue;

    void setupUI();
    void applyStyles();
    QPushButton* createStyledButton(const QString &text, const QString &bgColor, const QString &textColor);
    void updateDisplay(const QString &text);
};

#endif
