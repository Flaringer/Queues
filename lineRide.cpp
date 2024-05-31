#include <iostream>
#include <queue>
#include <stack>
#include <string>

class Visitor {
private:
    std::string name;
    int ticketNumber;

public:
    Visitor(const std::string& name, int ticketNumber)
        : name(name), ticketNumber(ticketNumber) {}

    void displayInfo() const {
        std::cout << "Name: " << name << ", Ticket Number: " << ticketNumber << std::endl;
    }
};

class RideLine {
private:
    std::queue<Visitor> queue;

    void reverseQueueHelper(std::queue<Visitor>& q) {
        if (q.empty()) {
            return;
        }
        Visitor frontVisitor = q.front();
        q.pop();
        reverseQueueHelper(q);
        q.push(frontVisitor);
    }

public:
    void enqueue(const Visitor& visitor) {
        queue.push(visitor);
    }

    void dequeue() {
        if (isEmpty()) {
            std::cerr << "Error: Cannot dequeue from an empty queue." << std::endl;
            return;
        }
        queue.pop();
    }

    void front() const {
        if (isEmpty()) {
            std::cerr << "Error: Queue is empty." << std::endl;
            return;
        }
        queue.front().displayInfo();
    }

    bool isEmpty() const {
        return queue.empty();
    }

    int size() const {
        return queue.size();
    }

    void displayAll() const {
        if (isEmpty()) {
            std::cerr << "Error: Queue is empty." << std::endl;
            return;
        }

        std::queue<Visitor> tempQueue = queue;
        while (!tempQueue.empty()) {
            tempQueue.front().displayInfo();
            tempQueue.pop();
        }
    }

    void reverse() {
        reverseQueueHelper(queue);
    }
};

void displayMenu() {
    std::cout << "1. Add a visitor to the queue\n";
    std::cout << "2. Remove a visitor from the queue\n";
    std::cout << "3. Display the front visitor\n";
    std::cout << "4. Check if the queue is empty\n";
    std::cout << "5. Display the total number of visitors\n";
    std::cout << "6. Display all visitors\n";
    std::cout << "7. Reverse the queue\n";
    std::cout << "8. Exit\n";
}

int main() {
    RideLine rideLine;
    int choice;
    std::string name;
    int ticketNumber;

    while (true) {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter visitor name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter ticket number: ";
                std::cin >> ticketNumber;
                rideLine.enqueue(Visitor(name, ticketNumber));
                break;

            case 2:
                rideLine.dequeue();
                break;

            case 3:
                rideLine.front();
                break;

            case 4:
                if (rideLine.isEmpty()) {
                    std::cout << "The queue is empty." << std::endl;
                } else {
                    std::cout << "The queue is not empty." << std::endl;
                }
                break;

            case 5:
                std::cout << "Total number of visitors: " << rideLine.size() << std::endl;
                break;

            case 6:
                rideLine.displayAll();
                break;

            case 7:
                rideLine.reverse();
                std::cout << "Queue reversed." << std::endl;
                break;

            case 8:
                return 0;

            default:
                std::cerr << "Invalid choice. Please try again." << std::endl;
        }
    }
}
