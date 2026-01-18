📊 Finance Tracker
Course Project #03 | Introduction to Programming Faculty of Mathematics and Informatics (FMI), Sofia University Winter Semester 2025/2026

👤 Author
Name: Stanislav Ivanov

Faculty Number: 6MI0600586

Compiler: VC (Visual C++)

Language: C++

📝 Project Overview
Finance Tracker is a robust, terminal-based financial management system designed to track personal income and expenses over a customizable period (up to 12 months). The application focuses on data integrity, providing users with analytical tools such as sorting, searching, financial forecasting, and visual representation of data through ASCII charts.

The project is built using pure C++ without high-level STL containers, demonstrating a strong grasp of memory management, arrays, and algorithmic logic.

✨ Key Features
⚙️ Profile Management
Custom Initialization: Setup your financial profile for a specific number of months.

Persistent Logic: Prevents accidental re-initialization once a profile is active.

💰 Transaction Tracking
Detailed Entry: Add income and expenses to specific months.

Smart Validation: Prevents negative entries and handles invalid non-numeric input gracefully.

🔍 Analysis & Insights
Search Function: Locate data for a specific month using its name (case-insensitive).

Sorting: Identify your "Top 3" months based on Income, Expense, or Balance using an optimized sorting algorithm.

Expense Ratio: Automatically calculates the percentage of income spent each month.

🔮 Forecasting & Visualization
Financial Projection: Uses linear regression logic to predict future savings or estimate when funds might run out based on current trends.

ASCII Charts: Generates a vertical bar chart to visualize financial fluctuations over time.

⌨️ Command Reference
Command	Argument	Description
SETUP	[months]	Initializes the profile (Range: 1-12).
ADD	-	Prompts for month index, income, and expense.
REPORT	-	Displays a formatted table of all active months.
SEARCH	[Month]	Searches data by month name (e.g., "January").
SORT	[Type]	Sorts Top 3 by INCOME, EXPENSE, or BALANCE.
FORECAST	[n]	Predicts savings after n months.
CHART	[Type]	Renders an ASCII bar chart for the chosen criteria.
EXIT	-	Displays a final report and terminates the program.

Export to Sheets

🛠 Technical Implementation
Core Principles
Modular Design: The code is decomposed into small, reusable functions with specific responsibilities (e.g., calculateFinancialStats, drawChart).

Input Resilience: Utilizes std::cin.clear() and std::cin.ignore() to ensure the program never crashes due to invalid user input.

Algorithm: Implements a custom sorting logic to handle indices, ensuring the original chronological order of data is preserved while displaying sorted results.

Mathematical Model
The Forecast feature uses the following linear model:

S 
predicted
​
 =S 
current
​
 +(n×Δ 
avg
​
 )
Where S is savings, n is months ahead, and Δ is the average monthly change.

🚀 Getting Started
Prerequisites
A C++ compiler (Visual Studio VC++, GCC, or Clang).

Running the App
Launch the executable.

Start by typing SETUP to define your tracking period.

Use ADD to input your first set of data.

Type CHART to see your progress visually!

🎓 Academic Integrity
This project was developed for educational purposes at Sofia University. It adheres to the constraint of using fundamental C++ features (arrays, C-strings) to demonstrate core programming proficiency.
