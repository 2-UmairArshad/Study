#include <iostream>
#include <string>
using namespace std;

//_________________Question 1____________
class Process {
public:
	int id;
	int time;
	Process* next;
	Process(int i, int t) {
		id = i;
		time = t;
		next = this;
	}
};

class CircularList {
public:
	Process* head;
	CircularList() {
		head = NULL;
	}

	void add(int id, int t) {
		Process* p = new Process(id, t);
		if (head == NULL) {
			head = p;
			return;
		}
		Process* cur = head;
		while (cur->next != head) cur = cur->next;
		cur->next = p;
		p->next = head;
	}

	void cycle(int q) {
		if (head == NULL) return;

		while (head != NULL) {
			Process* cur = head;
			Process* prev = NULL;
			bool completedInCycle = false;

			Process* last = head;
			while (last->next != head) {
				last = last->next;
			}

			do {
				Process* nextNode = cur->next;
				cur->time -= q;

				if (cur->time <= 0) {
					cout << "Process " << cur->id << " Completed" << endl;
					completedInCycle = true;

					if (cur == head && cur->next == head) {
						delete cur;
						head = NULL;
						return;
					}
					if (cur == head) {
						Process* temp = head;
						Process* lastNode = head;
						while (lastNode->next != head) {
							lastNode = lastNode->next;
						}
						head = head->next;
						lastNode->next = head;
						delete temp;
						cur = head;
						last = lastNode;
					}
					else {
						if (prev != NULL) {
							prev->next = cur->next;
						}
						delete cur;
						cur = nextNode;
					}
				}
				else {
					prev = cur;
					cur = cur->next;
				}

				if (head == NULL) return;

			} while (cur != head);
		}
	}
};

//________________Question 2_____________
class EditorHistory {
public:
	string undoStack[8];
	string redoStack[8];
	int utop;
	int rtop;

	EditorHistory() {
		utop = -1;
		rtop = -1;
	}

	void typeWord(string w) {
		if (utop < 7) {
			utop++;
			undoStack[utop] = w;
			rtop = -1;
		}
		else {
			cout << "  Warning: Editor is full (maximum 8 words)!" << endl;
		}
	}

	void undo() {
		if (utop == -1) {
			cout << "  Nothing to undo!" << endl;
			return;
		}
		if (rtop < 7) {
			rtop++;
			redoStack[rtop] = undoStack[utop];
		}
		utop--;
	}

	void redo() {
		if (rtop == -1) {
			cout << "  Nothing to redo!" << endl;
			return;
		}
		if (utop < 7) {
			utop++;
			undoStack[utop] = redoStack[rtop];
		}
		rtop--;
	}

	void show() {
		cout << "\nCurrent Editor Content: ";
		if (utop == -1) {
			cout << "(empty)";
		}
		else {
			for (int i = 0; i <= utop; i++) {
				cout << undoStack[i] << " ";
			}
		}
		cout << endl;
	}
};

int main() {
	int choice;
	cout << "=== Data Structures Assignment ===" << endl;
	cout << "1. Process Scheduling (Circular Linked List)" << endl;
	cout << "2. Text Editor with Undo/Redo (Stack)" << endl;
	cout << "Enter your choice (1 or 2): ";
	cin >> choice;
	cout << endl;

	if (choice == 1) {
		cout << "=== Process Scheduling with Round Robin ===" << endl;
		CircularList list;
		int n;
		cout << "Enter the number of processes: ";
		cin >> n;

		cout << "\nFor each process, enter:" << endl;
		for (int i = 0; i < n; i++) {
			int id, t;
			cout << "Process " << (i + 1) << " - Enter ID: ";
			cin >> id;
			cout << "Process " << (i + 1) << " - Enter burst time: ";
			cin >> t;
			list.add(id, t);
		}

		int quantum;
		cout << "\nEnter time quantum for Round Robin scheduling: ";
		cin >> quantum;
		cout << "\n--- Execution begins ---" << endl;
		list.cycle(quantum);
		cout << "--- All processes completed ---" << endl;
	}
	else if (choice == 2) {
		EditorHistory h;
		int q;

		cout << "=== Text Editor with Undo/Redo ===" << endl;
		cout << "Enter the number of commands you want to execute: ";
		cin >> q;

		cout << "\nAvailable commands:" << endl;
		cout << "  - type <word>  : Add a word to the editor" << endl;
		cout << "  - undo         : Undo the last action" << endl;
		cout << "  - redo         : Redo the last undone action" << endl;
		cout << "\nNote: Maximum 8 words can be stored in the editor.\n" << endl;

		while (q--) {
			string cmd;
			cout << "Enter command: ";
			cin >> cmd;

			if (cmd == "type") {
				string w;
				cout << "  Enter word to type: ";
				cin >> w;
				int oldTop = h.utop;
				h.typeWord(w);
				if (h.utop > oldTop) {
					cout << "  Word '" << w << "' added." << endl;
				}
			}
			else if (cmd == "undo") {
				h.undo();
				cout << "  Undo performed." << endl;
			}
			else if (cmd == "redo") {
				h.redo();
				cout << "  Redo performed." << endl;
			}
			else {
				cout << "  Invalid command! Please use 'type', 'undo', or 'redo'." << endl;
			}
		}

		h.show();
	}
	else {
		cout << "Invalid choice! Please run the program again and select 1 or 2." << endl;
	}

	return 0;
}