/**
*
* Solution to course project # 03
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Staislav Ivanov
* @idnumber 6MI0600586
* @compiler VC
*
* The implementation of the finance tracker project.
*
*/

#include <iostream>

const int PROFILE_ROW = 2;
const int MONTHS_COUNT = 12;
const int COMMAND_MAX_SIZE = 1024;
const int SETUP_INDEX = 0;
const int ADD_INDEX = 1;
const int REPORT_INDEX = 2;
const int SEARCH_INDEX = 3;
const int SORT_INDEX = 4;
const int FORECAST_INDEX = 5;
const int CHART_INDEX = 6;
const int EXIT_INDEX = 7;
const int FAIL_CODE_INDEX = -1;
const int COMMANDS_COUNT = 8;
const int IGNORE_CHARACTERS_COUNT = 1024;
const int MONTHS_MIN_VALUE = 1;
const int MONTHS_MAX_VALUE = 12;
const int PROFILE_INCOME_INDEX = 0;
const int PROFILE_EXPENSE_INDEX = 1;
const int DEFAULT_MONTH_EMPTY_VALUE = 0;
const double PERCENT_MULTIPLIER = 100.0;
const int CRITERIAS_COUNT = 3;
const int SORTING_TOP_COUNT = 3;
const char* INCOME_LABEL = "income";
const char* EXPENSE_LABEL = "expense";
const char* COMMANDS[] = {
		"SETUP", "ADD", "REPORT", "SEARCH", "SORT", "FORECAST",
		"CHART", "EXIT"
};
const char* MONTH_NAMES[] = {
	"JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE",
		"JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"
};
const char* MONTH_ABBREVIATIONS[MONTHS_MAX_VALUE] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
const char* CRITERIAS[CRITERIAS_COUNT] = {
	"INCOME",
	"EXPENSE",
	"BALANCE"
};
bool isLetterLowerCase(const char letter) {
	return letter >= 'a' && letter <= 'z';
}
bool isLetterUpperCase(const char letter) {
	return letter >= 'A' && letter <= 'Z';
}
void toUpper(char* word) {

	if (!word) {
		return;
	}

	while (*word) {
		if (isLetterLowerCase(*word)) {
			*word = *word - 'a' + 'A';
		}

		word++;
	}

}
bool areEqual(const char* firstString, const char* secondString) {
	if (!firstString || !secondString) {
		return false;
	}

	while (*firstString && *secondString) {
		if (*firstString != *secondString) {
			return false;
		}
		firstString++;
		secondString++;
	}

	return *firstString == '\0' && *secondString == '\0';
}
int getCommandIndex(const char* command) {
	if (!command) {
		return FAIL_CODE_INDEX;
	}



	for (int i = 0; i < COMMANDS_COUNT; i++)
	{
		if (areEqual(command, COMMANDS[i])) {
			return i;
		}
	}

	return FAIL_CODE_INDEX;
}
bool isInputInvalid() {
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(IGNORE_CHARACTERS_COUNT, '\n');
		std::cout << "Error: Please enter a valid number.\n";

		return true;
	}

	return false;
}
void setupProfile(double profile[PROFILE_ROW][MONTHS_COUNT], int& profileMonths, bool& isProfileSetup) {

	if (isProfileSetup) {
		std::cout << "Error: Profile is already set up!\n";
		return;
	}

	while (true) {
		std::cout << "Enter number of months: ";
		std::cin >> profileMonths;

		if (isInputInvalid()) {
			continue;
		}

		if (profileMonths < MONTHS_MIN_VALUE || profileMonths > MONTHS_MAX_VALUE) {
			std::cout << "Invalid number of months! Range: "
				<< MONTHS_MIN_VALUE << " - " << MONTHS_MAX_VALUE << ".\n";
			continue;
		}

		break;
	}

	for (int month = 0; month < profileMonths; month++) {
		profile[PROFILE_INCOME_INDEX][month] = DEFAULT_MONTH_EMPTY_VALUE;
		profile[PROFILE_EXPENSE_INDEX][month] = DEFAULT_MONTH_EMPTY_VALUE;
	}

	std::cout << "Profile created successfully.\n";
	isProfileSetup = true;
}
double readMoneyValue(const char* label) {
	double value;
	while (true) {
		std::cout << "Enter " << label << ": ";
		std::cin >> value;

		if (isInputInvalid()) continue;

		if (value < 0) {
			std::cout << "Error: " << label << " cannot be negative!\n";
			continue;
		}
		return value;
	}
}

int readTargetMonth(int maxMonths) {
	int month;
	while (true) {
		std::cout << "Enter month (1-" << maxMonths << "): ";
		std::cin >> month;

		if (isInputInvalid()) continue;

		if (month < 1 || month > maxMonths) {
			std::cout << "Error: Month must be between 1 and " << maxMonths << ".\n";
			continue;
		}
		return month;
	}
}
void printCapitalized(const char* word) {
	if (!word) {
		return;
	}


	std::cout << *word;
	word++;
	while (*word) {
		char letter = *word;
		if (isLetterUpperCase(letter)) {
			std::cout << (char)(letter - 'A' + 'a');
		}
		else {
			std::cout << letter;
		}
		
		word++;
	}
}
void addMonthData(double profile[PROFILE_ROW][MONTHS_COUNT], int profileMonths, bool isProfilSetup) {
	if (!isProfilSetup) {
		std::cout << "The profile is not set up.You need to go and set it up first.\n";
		return;
	}


	int month = readTargetMonth(profileMonths);

	double income = readMoneyValue(INCOME_LABEL);
	double expense = readMoneyValue(EXPENSE_LABEL);

	profile[PROFILE_INCOME_INDEX][month - 1] += income;
	profile[PROFILE_EXPENSE_INDEX][month - 1] += expense;

	double currentBalance = profile[PROFILE_INCOME_INDEX][month - 1] - profile[PROFILE_EXPENSE_INDEX][month - 1];

	std::cout << "Balance for ";
	printCapitalized(MONTH_NAMES[month - 1]);
	std::cout << " = " << (currentBalance > 0 ? "+" : "") << currentBalance << "\n";
}

void generateReportTable(const double profile[PROFILE_ROW][MONTHS_COUNT], int profileMonths, double& totalIncome, double& totalExpense, int& activeMonths) {
	std::cout.precision(2);
	std::cout.setf(std::ios::fixed, std::ios::floatfield);

	std::cout << "Month | Income | Expense | Balance " << std::endl;
	std::cout << "---------------------------------- " << std::endl;


	for (int month = 0; month < profileMonths; month++) {
		if (profile[PROFILE_INCOME_INDEX][month] != DEFAULT_MONTH_EMPTY_VALUE ||
			profile[PROFILE_EXPENSE_INDEX][month] != DEFAULT_MONTH_EMPTY_VALUE) {
			double currentIncome = profile[PROFILE_INCOME_INDEX][month];
			double currentExpense = profile[PROFILE_EXPENSE_INDEX][month];
			double currentBalance = currentIncome - currentExpense;

			totalIncome += currentIncome;
			totalExpense += currentExpense;
			activeMonths++;

			std::cout << MONTH_ABBREVIATIONS[month] << " | " << currentIncome << " | " << currentExpense << " | " << currentBalance << std::endl;
		}
	}

	std::cout << "------------------------------------------------------------" << std::endl;

	std::cout << "Total income: " << totalIncome << std::endl;
	std::cout << "Total expense: " << totalExpense << std::endl;
}

void displayReport(const double profile[PROFILE_ROW][MONTHS_COUNT], int profileMonths, bool isProfileSetup) {
	if (!isProfileSetup) {
		std::cout << "The profile is not set up.You need to go and set it up first.\n";
		return;
	}

	double totalIncome = 0;
	double totalExpense = 0;
	int activeMonths = 0;
	generateReportTable(profile, profileMonths, totalIncome, totalExpense, activeMonths);


	if (activeMonths > 0) {
		double averageBalance = (totalIncome - totalExpense) / activeMonths;
		std::cout << "Average Balance: " << (averageBalance > 0 ? "+" : "") << averageBalance << std::endl;
	}
	else {
		std::cout << "Average Balance: 0.00 (No active months)" << std::endl;
	}
}
int getMonthIndexByName(const char* monthName) {
	for (int i = 0; i < MONTHS_COUNT; i++) {
		if (areEqual(monthName, MONTH_NAMES[i])) {
			return i;
		}
	}
	return FAIL_CODE_INDEX;
}

void printRatioInfo(double income, double expense) {
	if (income > 0) {
		double ratio = (expense / income) * PERCENT_MULTIPLIER;
		std::cout << "Expense ratio: " << ratio << "%\n";
	}
	else if (expense > 0) {
		std::cout << "Expense ratio: 100% (No income, only expenses)\n";
	}
	else {
		std::cout << "Expense ratio: 0.00% (No activity)\n";
	}
}
void searchByMonth(const double profile[PROFILE_ROW][MONTHS_COUNT], int profileMonths, bool isProfileSetup) {
	if (!isProfileSetup) {
		std::cout << "The profile is not set up.You need to go and set it up first.\n";
		return;
	}

	char targetMonth[COMMAND_MAX_SIZE];
	std::cout << "Enter month name to search: ";
	std::cin >> targetMonth;
	toUpper(targetMonth);

	int monthIndex = getMonthIndexByName(targetMonth);

	if (monthIndex == FAIL_CODE_INDEX || monthIndex >= profileMonths) {
		std::cout << "Error: Invalid month name or month not in profile range.\n";
		return;
	}

	double income = profile[PROFILE_INCOME_INDEX][monthIndex];
	double expense = profile[PROFILE_EXPENSE_INDEX][monthIndex];
	double balance = income - expense;

	std::cout.precision(2);
	std::cout.setf(std::ios::fixed, std::ios::floatfield);

	std::cout << "Income: " << income << "\n";
	std::cout << "Expense: " << expense << "\n";
	std::cout << "Balance: " << (balance > 0 ? "+" : "") << balance << "\n";

	printRatioInfo(income, expense);
}
int getIndexOfCriteria(const char* criteria) {


	if (!criteria) {
		return FAIL_CODE_INDEX;
	}
	for (int i = 0; i < CRITERIAS_COUNT; i++) {
		if (areEqual(criteria, CRITERIAS[i])) {
			return i;
		}
	}
	return FAIL_CODE_INDEX;


}
double getValueByCriteriaIndex(const double profile[PROFILE_ROW][MONTHS_COUNT], int monthIdx, int criteriaIndex) {
	if (criteriaIndex == 0) {
		return profile[PROFILE_INCOME_INDEX][monthIdx];
	}

	if (criteriaIndex == 1) {
		return profile[PROFILE_EXPENSE_INDEX][monthIdx];
	}

	if (criteriaIndex == 2) {
		return profile[PROFILE_INCOME_INDEX][monthIdx] - profile[PROFILE_EXPENSE_INDEX][monthIdx];
	}

	return FAIL_CODE_INDEX;
}
void swap(int& a, int& b) {

	int temp = a;
	a = b;
	b = temp;
}
void sortIndicesByCriteria(const double profile[PROFILE_ROW][MONTHS_COUNT], int profileMonths, int* indices, int criteriaIndex) {
	for (int i = 0; i < profileMonths - 1; i++) {
		int maxIdx = i;
		for (int j = i + 1; j < profileMonths; j++) {
			double valCurrent = getValueByCriteriaIndex(profile, indices[j], criteriaIndex);
			double valMax = getValueByCriteriaIndex(profile, indices[maxIdx], criteriaIndex);

			if (valCurrent > valMax) {
				maxIdx = j;
			}
		}
		swap(indices[i], indices[maxIdx]);
	}
}
void printTopResults(const double profile[PROFILE_ROW][MONTHS_COUNT], int profileMonths, const int* indices, int criteriaIndex) {
	int topCount = (profileMonths < SORTING_TOP_COUNT) ? profileMonths : SORTING_TOP_COUNT;

	std::cout.precision(2);
	std::cout.setf(std::ios::fixed, std::ios::floatfield);

	for (int i = 0; i < topCount; i++) {
		int mIdx = indices[i];
		double value = getValueByCriteriaIndex(profile, mIdx, criteriaIndex);

		std::cout << MONTH_ABBREVIATIONS[mIdx] << ": ";
	
		if (criteriaIndex == 2 && value > 0) std::cout << "+";
		std::cout << value << "\n";
	}
}
void sortProfile(const double profile[PROFILE_ROW][MONTHS_COUNT], int profileMonths, bool isProfileSetup) {
	if (!isProfileSetup) {
		std::cout << "The profile is not set up. You need to go and set it up first.\n";
		return;
	}

	char criteria[COMMAND_MAX_SIZE];
	std::cout << "Enter criteria (income, expense, balance): ";
	std::cin >> criteria;
	toUpper(criteria);

	int criteriaIndex = getIndexOfCriteria(criteria);

	if (criteriaIndex == FAIL_CODE_INDEX) {
		std::cout << "Error: Invalid criteria. Please enter income, expense, or balance.\n";
		return;
	}

	int indices[MONTHS_MAX_VALUE];
	for (int i = 0; i < profileMonths; i++) {
		indices[i] = i;
	}

	sortIndicesByCriteria(profile, profileMonths, indices, criteriaIndex);
	
	std::cout << "Sorted by monthly " << criteria << " (descending):\n";

	printTopResults(profile, profileMonths, indices, criteriaIndex);
}
void handleCommand(int commandIndex, double profile[PROFILE_ROW][MONTHS_COUNT], int& profileMonths, bool& isProfileSetUp) {

	switch (commandIndex) {
	case SETUP_INDEX:
		setupProfile(profile, profileMonths, isProfileSetUp);
		break;
	case ADD_INDEX:
		addMonthData(profile, profileMonths, isProfileSetUp);
		break;
	case REPORT_INDEX:
		displayReport(profile, profileMonths, isProfileSetUp);
		break;
	case SEARCH_INDEX:
		searchByMonth(profile, profileMonths, isProfileSetUp);
		break;
	case SORT_INDEX:
		sortProfile(profile, profileMonths, isProfileSetUp);
		break;
	}
	
}
void runApplication() {
	int profileMonths = 0;
	double profile[PROFILE_ROW][MONTHS_COUNT] = { 0 };
	char command[COMMAND_MAX_SIZE];
	bool isProfileSetup = false;
	std::cout << "Enter a command.\n";
	std::cin >> command;

	while (true) {
		toUpper(command);
		int commandIndex = getCommandIndex(command);

		if (commandIndex == EXIT_INDEX) {

			return;
		}

		if (isProfileSetup && commandIndex == SETUP_INDEX) {
			std::cout << "The profile has already been set up.\n";
			std::cin >> command;
			continue;
		}

		if (commandIndex == FAIL_CODE_INDEX) {
			std::cout << "Error: Unknown command.Try again.\n";
			std::cin >> command;
			continue;
		}

		handleCommand(commandIndex, profile, profileMonths, isProfileSetup);

		std::cin >> command;
	}
}

int main()
{
	runApplication();

	return 0;
}

