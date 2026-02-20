#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace::std;
string fileName;
ofstream ofs(fileName);

class myString {
private:
	char arr[26];
	string name;
	bool announce = false;

public:
	myString(string str = "") : name(str), announce(!str.empty()) {
		initString(); 
	}

	int size() const {
		for (int i = 0; i < 26; i++) {
			if (arr[i] == '~' || arr[i] == '\0') {
				return i;
			}
		}
		return 25; 
	}

	void addStart(myString str, bool& methodStatus) {
		int currentSize = size();
		int newStringSize = str.size();
		methodStatus = true;

		for (int i = 0; i < newStringSize; i++) {
			bool charStatus;
			char c = str.charAt(i, charStatus);
			if (!charStatus || c == '~') {
				methodStatus = false;
				printLog(-1);
				return;
			}
		}

		if (currentSize + newStringSize > 25) {
			methodStatus = false;
			printLog(-2);
			return;
		}

		for (int i = currentSize - 1; i >= 0; i--) {
			arr[i + newStringSize] = arr[i];
		}

		for (int i = 0; i < newStringSize; i++) {
			arr[i] = str.charAt(i, methodStatus);
		}

		arr[currentSize + newStringSize] = '~';
		methodStatus = true;
		printLog(1);
	}

	void addEnd(myString str, bool& methodStatus) {
		int currentSize = size();
		int newStringSize = str.size();
		methodStatus = true;

		for (int i = 0; i < newStringSize; i++) {
			bool charStatus;
			char c = str.charAt(i, charStatus);
			if (!charStatus || c == '~') {
				methodStatus = false;
				printLog(-1);
				return;
			}
		}

		if (currentSize + newStringSize > 25) {
			methodStatus = false;
			printLog(-2);
			return;
		}

		for (int i = 0; i < newStringSize; i++) {
			arr[currentSize + i] = str.charAt(i, methodStatus);
		}

		arr[currentSize + newStringSize] = '~';
		methodStatus = true;
		printLog(2);
	}

	myString partString(int startPos, int length, bool& methodStatus) {
		int currentSize = this->size();
		myString str;
		methodStatus = true;

		if (startPos < 0 || startPos > 25) {
			methodStatus = false;
			printLog(-3);
			return str;
		}

		if (length <= 0 || startPos == currentSize) {
			str.initString();
			printLog(-4);
			methodStatus = false;
			return str;
		}

		string strTemp;
		for (int i = startPos; i < startPos + length && i < currentSize; i++) {
			if (arr[i] == '~') break;
			strTemp += arr[i];
		}

		str.setString(strTemp, methodStatus);
		return str;
	}

	void replPartString(myString str, int startPos, bool& methodStatus) {
		int currentSize = size();
		int newStringSize = str.size();
		methodStatus = true;

		for (int i = 0; i < newStringSize; i++) {
			bool charStatus;
			char c = str.charAt(i, charStatus);
			if (!charStatus || c == '~') {
				methodStatus = false;
				printLog(-1);
				return;
			}
		}

		if (startPos < 0 || startPos + newStringSize > 25) {
			methodStatus = false;
			printLog(-2);
			return;
		}

		for (int i = 0; i < newStringSize; i++) {
			arr[startPos + i] = str.charAt(i, methodStatus);
		}

		int newLength = currentSize + newStringSize;
		if (newLength < currentSize) {
			arr[newLength] = '~';
		}

		methodStatus = true;
		printLog(3);
	}

	void replWholeString(myString str, bool& methodStatus) {
		int newStringSize = str.size();
		methodStatus = true;

		for (int i = 0; i < newStringSize; i++) {
			bool charStatus;
			char c = str.charAt(i, charStatus);
			if (!charStatus || c == '~') {
				methodStatus = false;
				printLog(-1);
				return;
			}
		}

		if (newStringSize > 25) {
			methodStatus = false;
			printLog(-2);
			return;
		}

		initString();
		for (int i = 0; i < newStringSize; i++) {
			arr[i] = str.charAt(i, methodStatus);
		}

		arr[newStringSize] = '~';
		methodStatus = true;
		printLog(4);
	}

	bool emptyString() const {
		return (arr[0] == '\0' || arr[0] == '~');
	}

	bool fullString() const {
		return (size() >= 25);
	}

	bool compareString(const myString& str) const {
		int currentSize = size();
		if (str.size() != currentSize) {
			return false;
		}

		for (int i = 0; i < currentSize; i++) {
			bool charStatus;
			if (arr[i] != str.charAt(i, charStatus)) {
				return false;
			}
		}
		return true;
	}

	char charAt(int pos, bool& methodStatus) const {
		if (pos < 0 || pos >= size()) {
			methodStatus = false;
			printLog(-5);
			return '\0'; 
		}
		methodStatus = true;
		return arr[pos];
	}

	void initString() {
		fill_n(arr, 26, '\0'); 
	}

	void setString(const string& str, bool& methodStatus) {
		initString();
		methodStatus = true;

		// Check length
		if (str.size() > 25) {
			methodStatus = false;
			printLog(-2);
			return;
		}

		for (size_t i = 0; i < str.length(); i++) {
			if (str.at(i) == '~') {
				methodStatus = false;
				printLog(-1);
				return;
			}
			arr[i] = str.at(i);
		}

		arr[str.length()] = '~';
		printLog(5);
	}

	string getString() const {
		string str;
		int strSize = size(); 
		str.reserve(strSize); 
		for (int i = 0; i < strSize; i++) {
			str += arr[i];
		}
		return str;
	}

	void printString() const {
		cout << getString(); 
	}

	void printLog(int code) const {
		if (!this->announce) return;

		cout << setw(20) << left << "Program Action";
		ofs << setw(20) << left << "Program Action";

		switch (code) {
		case -5:
			cout << "Error (" << code << "): Position either has an empty char or is outside of the range." << endl;
			ofs << "Error (" << code << "): Position either has an empty char or is outside of the range." << endl;
			break;
		case -4:
			cout << "Error (" << code << "): Position is the same value as the string's size, or length is < 0." << endl;
			ofs << "Error (" << code << "): Position is the same value as the string's size, or length is < 0." << endl;
			break;
		case -3:
			cout << "Error (" << code << "): Position is outside of the range (<0 or >25)." << endl;
			ofs << "Error (" << code << "): Position is outside of the range (<0 or >25)." << endl;
			break;
		case -2:
			cout << "Error (" << code << "): Input string is too large, result exceeds 25 characters." << endl;
			ofs << "Error (" << code << "): Input string is too large, result exceeds 25 characters." << endl;
			break;
		case -1:
			cout << "Error (" << code << "): Input string has an illegal character ('~')" << endl;
			ofs << "Error (" << code << "): Input string has an illegal character ('~')" << endl;
			break;
		case 0:
			cout << this->name << " now contains '" << this->getString() << "'." << endl;
			ofs << this->name << " now contains '" << this->getString() << "'." << endl;
			break;
		case 1:
			cout << "Successfully added the input string to start of string." << endl;
			ofs << "Successfully added the input string to start of string." << endl;
			this->printLog(0);
			break;
		case 2:
			cout << "Successfully added the input string to end of string." << endl;
			ofs << "Successfully added the input string to end of string." << endl;
			this->printLog(0);
			break;
		case 3:
			cout << "Successfully replaced part of string." << endl;
			ofs << "Successfully replaced part of string." << endl;
			this->printLog(0);
			break;
		case 4:
			cout << "Successfully replaced the entire string." << endl;
			ofs << "Successfully replaced the entire string." << endl;
			this->printLog(0);
			break;
		case 5:
			cout << "Successfully set the string's value." << endl;
			ofs << "Successfully set the string's value." << endl;
			this->printLog(0);
			break;
		default:
			cout << "Unknown action code: " << code << endl;
			ofs << "Unknown action code: " << code << endl;
			break;
		}
	}

	friend istream& operator>>(istream& input, myString& str) {
		string tempStr;
		input >> tempStr;

		if (tempStr.size() > 25) {
			str.printLog(-2); 
			return input;
		}

		bool methodStatus;
		str.setString(tempStr, methodStatus);

		return input;
	}

	friend ostream& operator<<(ostream& output, const myString& str) {
		output << str.getString(); 
		return output;
	}
};

void printLog(int code, const string& name, const myString& str, int pos, const string str2 = "ERROR");

int main() {
	char userInputChar = 'n';
	char tempChar;
	string userInputStr;
	string resultStr;
	string userName;
	int userInputInt = 0;
	int userInputInt2 = 0;
	int userStrChoice = 0;

	string str1Name = "Instance 1";
	string str2Name = "Instance 2";
	myString str1(str1Name);
	myString str2(str2Name);
	myString tempStr("Temp");
	bool tempBool = false; 

	cout << "Hello user! Please enter your name: ";
	cin >> userName;
	cout << "Perfect! Welcome and thank you for using this program, " << userName << "!" << endl;
	cout << "Now, please enter the name of the output file you would like to create/edit: ";
	cin >> fileName;

	ofs.close();
	ofs.open(fileName);
	if (!ofs.is_open()) {
		cout << "***ERROR*** File failed to open!" << endl;
		return 1; 
	}

	do {
		cout << "Please select an option from the below menu by entering the integer corresponding to it!" << endl;
		cout << left;
		cout << setw(60) << "1. Set a string" << "2. Get a string" << endl;
		cout << setw(60) << "3. Add to start of string" << "4. Add to end of string" << endl;
		cout << setw(60) << "5. Print part of a String" << "6. Replace part of a string" << endl;
		cout << setw(60) << "7. Replace whole string" << "8. Check if a string is empty" << endl;
		cout << setw(60) << "9. Check if a string is full" << "10. Compare 2 Strings" << endl;
		cout << setw(60) << "11. Find the char at a pos in a string" << "12. Print a string" << endl;
		cout << setw(60) << "13. Initialize a String" << endl;
		cin >> userInputInt;

		while (userInputInt < 1 || userInputInt > 13) { 
			cout << "Please enter a valid option (1 - 13): ";
			cin >> userInputInt;
		}

		cout << setw(30) << "1. String 1" << "2. String 2" << endl;
		cout << "Please select one of the above listed strings: ";
		cin >> userStrChoice;

		while (userStrChoice != 1 && userStrChoice != 2) {
			cout << "Please enter a valid option (1 or 2): ";
			cin >> userStrChoice;
		}

		switch (userInputInt) {
		case 1: {
			bool methodStatus = true;
			cout << "Please enter a string to set the string to: ";
			cin >> userInputStr;
			
			if (userStrChoice == 1) {
				printLog(1, str1Name, tempStr, userInputInt, userInputStr);
				str1.setString(userInputStr, methodStatus);
			}
			else {
				printLog(1, str2Name, tempStr, userInputInt, userInputStr);
				str2.setString(userInputStr, methodStatus);
			}
			break;
		}
		case 2: {
			if (userStrChoice == 1) {
				printLog(2, str1Name, str1.getString(), userInputInt, userInputStr);
				resultStr = str1.getString();
			}
			else {
				printLog(2, str2Name, str2.getString(), userInputInt, userInputStr);
				resultStr = str2.getString();
			}
			cout << "The string you selected currently reads as: '" << resultStr << "'" << endl;
			break;
		}

		case 3: {
			bool methodStatus = true;
			cout << "Please enter what you would like to add to the start of the string: ";
			cin >> userInputStr;
			tempStr.setString(userInputStr, methodStatus);
			if (userStrChoice == 1) {
				printLog(3, str1Name, tempStr, userInputInt, userInputStr);
				if (!methodStatus) { break; }
				str1.addStart(tempStr, methodStatus);
			}
			else {
				printLog(3, str2Name, tempStr, userInputInt, userInputStr);
				if (!methodStatus) { break; }
				str2.addStart(tempStr, methodStatus);
			}
			break;
		}

		case 4: {
			bool methodStatus = true;
			cout << "Please enter what you would like to add to the end of the string: ";
			cin >> userInputStr;
			tempStr.setString(userInputStr, methodStatus);
			if (userStrChoice == 1) {
				printLog(4, str1Name, tempStr, userInputInt, userInputStr);
				if (!methodStatus) { break; }
				str1.addEnd(tempStr, methodStatus);
			}
			else {
				printLog(4, str2Name, tempStr, userInputInt, userInputStr);
				if (!methodStatus) { break; }
				str2.addEnd(tempStr, methodStatus);
			}
			break;
		}
		case 5: {
			bool methodStatus = true;
			if (userStrChoice == 1) {
				cout << "Please enter the starting position you would like to print from the string (" << str1.getString() << "): ";
				cin >> userInputInt;
				cout << "Please enter the length from the starting position you would like to print from the string (" << str1.getString() << "): ";
				cin >> userInputInt2;
				printLog(5, str1Name, tempStr, userInputInt);
				tempStr = str1.partString(userInputInt - 1, userInputInt2, methodStatus);
				if (!methodStatus) { break; }
				cout << "The portion of the string you selected is currently : '";
				tempStr.printString();
				cout << "'." << endl;
			}
			else {
				cout << "Please enter the starting position you would like to print from the string (" << str2.getString() << "): ";
				cin >> userInputInt;
				cout << "Please enter the length from the starting position you would like to print from the string (" << str2.getString() << "): ";
				cin >> userInputInt2;
				printLog(5, str2Name, tempStr, userInputInt);
				tempStr = str2.partString(userInputInt - 1, userInputInt2, methodStatus);
				if (!methodStatus) { break; }
				cout << "The portion of the string you selected is currently : '";
				tempStr.printString();
				cout << "'." << endl;
			}
			break;
		}
		case 6: {
			bool methodStatus = true;
			switch (userStrChoice) {
			case 1: {
				cout << "Please enter the starting position you would like to replace in the string (" << str1.getString() << "): ";
				cin >> userInputInt;
				cout << "Please enter the string you would like to replace this portion with: ";
				cin >> userInputStr;
				printLog(6, str1Name, tempStr, userInputInt, userInputStr);
				tempStr.setString(userInputStr, methodStatus);
				if (!methodStatus) { break; }
				str1.replPartString(tempStr, userInputInt - 1, methodStatus);
				break;
			}
			case 2: {
				cout << "Please enter the starting position you would like to replace in the string (" << str2.getString() << "): ";
				cin >> userInputInt;
				cout << "Please enter the string you would like to replace this portion with: ";
				cin >> userInputStr;
				printLog(6, str2Name, tempStr, userInputInt, userInputStr);
				tempStr.setString(userInputStr, methodStatus);
				if (!methodStatus) { break; }
				str2.replPartString(tempStr, userInputInt - 1, methodStatus);
				break;
			}
			}
			break;
		}

		case 7: {
			bool methodStatus = true;
			cout << "Please enter a string to set the string to: ";
			cin >> userInputStr;
			tempStr.setString(userInputStr, methodStatus);

				switch (userStrChoice) {
				case 1:
					printLog(7, str1Name, tempStr, userInputInt, userInputStr);
					if (!methodStatus) { break; }
					str1.replWholeString(tempStr, methodStatus);
					
					break;
				case 2:
					printLog(7, str2Name, tempStr, userInputInt, userInputStr);
					if (!methodStatus) { break; }
					str2.replWholeString(tempStr, methodStatus);
					break;
				}
			break;
		}

		case 8: {
				switch (userStrChoice) {
				case 1:
					tempBool = str1.emptyString();
					cout << "String 1 is " << (tempBool ? "" : "not ") << "empty." << endl;
					printLog(8, str1Name, tempStr, userInputInt);
					break;
				case 2:
					tempBool = str2.emptyString();
					cout << "String 2 is " << (tempBool ? "" : "not ") << "empty." << endl;
					printLog(8, str2Name, tempStr, userInputInt);
					break;
				}
			break;
		}

		case 9: {
			switch (userStrChoice) {
			case 1:
				tempBool = str1.fullString();
				cout << "String 1 is " << (tempBool ? "" : "not ") << "full." << endl;
				printLog(9, str1Name, tempStr, userInputInt);
				break;
			case 2:
				tempBool = str2.fullString();
				cout << "String 2 is " << (tempBool ? "" : "not ") << "full." << endl;
				printLog(9, str2Name, tempStr, userInputInt);
				break;
			}
			break;
		}

		case 10: {
			bool methodStatus = true;
			cout << "Please enter the string you would like to compare: ";
			cin >> userInputStr;
			tempStr.setString(userInputStr, methodStatus);

			switch (userStrChoice) {
			case 1:
				printLog(10, str1Name, tempStr, userInputInt, userInputStr);
				if (!methodStatus) { break; }
				tempBool = str1.compareString(tempStr);
				cout << "The string entered (" << tempStr << ") is " << (tempBool ? "" : "not ") << "the same as the string selected (" << str1 << ")." << endl;
				break;
			case 2:
				printLog(10, str2Name, tempStr, userInputInt, userInputStr);
				if (!methodStatus) { break; }
				tempBool = str2.compareString(tempStr);
				cout << "The string entered (" << tempStr << ") is " << (tempBool ? "" : "not ") << "the same as the string selected (" << str2 << ")." << endl;
				break;
			}
			break;
		}

		case 11: {
			bool methodStatus = true;
			cout << "Please enter the position in the string you would like to search: ";
			cin >> userInputInt2;

			switch (userStrChoice) {
			case 1:
				tempChar = str1.charAt(userInputInt2 - 1, methodStatus);
				printLog(11, str1Name, tempStr, userInputInt, userInputStr);
				if (!methodStatus) { break; }
				cout << "The character at position " << userInputInt2 << " of string 1 (" << str1 << ") is '" << tempChar << "'." << endl;
				break;
			case 2:
				tempChar = str2.charAt(userInputInt2 - 1, methodStatus);
				printLog(11, str1Name, tempStr, userInputInt, userInputStr);
				if (!methodStatus) { break; }
				cout << "The character at position " << userInputInt2 << " of string 2 (" << str2 << ") is '" << tempChar << "'." << endl;
				break;
			}
			break;
		}

		case 12: {
			switch (userStrChoice) {
			case 1:
				cout << "String 1 is currently '";
				str1.printString();
				cout << "'." << endl;
				printLog(12, str1Name, tempStr, userInputInt);
				break;
			case 2:
				cout << "String 2 is currently '";
				str2.printString();
				cout << "'." << endl;
				printLog(12, str2Name, tempStr, userInputInt);
				break;
			}
			break;
		}

		case 13: {
			switch (userStrChoice) {
			case 1:
				str1.initString();
				printLog(13, str1Name, tempStr, userInputInt);
				break;
			case 2:
				str2.initString();
				printLog(13, str2Name, tempStr, userInputInt);
				break;
			}


			}
		}
		cout << "Would you like to continue? Enter 'y' or 'n' : ";
		cin >> userInputChar;
	}while (userInputChar == 'y' || userInputChar == 'Y');
	
	cout << "Shutting down, thank you for using this program " << userName << "!" << endl;
	ofs.close();
	system("pause");
	return 0;
}

void printLog(int code, const string& name, const myString& str, int pos, const string str2) {
	cout << setw(20) << left << "User Action";
	ofs << setw(20) << left << "User Action";

	switch (code) {
	case 1:
		cout << "User tried setting string " << name << " to " << str2 << "." << endl;
		ofs << "User tried setting string " << name << " to " << str2 << "." << endl;
		break;
	case 2:
		cout << "User got string " << name << "." << endl;
		ofs << "User got string " << name << "." << endl;
		break;
	case 3:
		cout << "User tried adding " << str2 << " to the start of string " << name << "." << endl;
		ofs << "User tried adding " << str2 << " to the start of string " << name << "." << endl;
		break;
	case 4:
		cout << "User tried adding " << str2 << " to the end of string " << name << "." << endl;
		ofs << "User tried adding " << str2 << " to the end of string " << name << "." << endl;
		break;
	case 5:
		cout << "User tried printing part of string " << name << "." << endl;
		ofs << "User tried printing part of string " << name << "." << endl;
		break;
	case 6:
		cout << "User tried replacing part of string " << name << " with " << str2 << " at position " << pos << "." << endl;
		ofs << "User tried replacing part of string " << name << " with " << str2 << " at position " << pos << "." << endl;
		break;
	case 7:
		cout << "User tried replacing all of string " << name << " with " << str2 << "." << endl;
		ofs << "User tried replacing all of string " << name << " with " << str2 << "." << endl;
		break;
	case 8:
		cout << "User checked if string " << name << " was empty." << endl;
		ofs << "User checked if string " << name << " was empty." << endl;
		break;
	case 9:
		cout << "User checked if string " << name << " was full." << endl;
		ofs << "User checked if string " << name << " was full." << endl;
		break;
	case 10:
		cout << "User compared " << str2 << " with string " << name << "." << endl;
		ofs << "User compared " << str2 << " with string " << name << "." << endl;
		break;
	case 11:
		cout << "User tried to find the character at pos " << pos << " in string " << name << "." << endl;
		ofs << "User tried to find the character at pos " << pos << " in string " << name << "." << endl;
		break;
	case 12:
		cout << "User printed string " << name << "." << endl;
		ofs << "User printed string " << name << "." << endl;
		break;
	case 13:
		cout << "User initialized string " << name << "." << endl;
		ofs << "User initialized string " << name << "." << endl;
		break;
	default:
		cout << "Unknown action code: " << code << endl;
		ofs << "Unknown action code: " << code << endl;
		break;
	}
}