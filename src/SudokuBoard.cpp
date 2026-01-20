#include "SudokuBoard.h"
#include "SudokuCell.h"

/**
 * @brief Construct a new Sudoku Board object, setting up the UI and initializing the puzzle.
 */
SudokuBoard::SudokuBoard(QWidget *parent, int numberOfGivenCells) : QWidget(parent) {
    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(12, 12, 12, 12);
    root->setSpacing(12);

    auto *grid = new QGridLayout();
    grid->setSpacing(0);
    grid->setContentsMargins(0, 0, 0, 0);

    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            auto *cell = new SudokuCell(r, c, this);
            all_cells[r][c] = cell;
            connect(cell, &SudokuCell::activated, this, &SudokuBoard::onCellActivated); // Notify when cell is clicked
            grid->addWidget(cell, r, c);
        }
    }

    // Add Hint, Check, and Solve buttons
    auto *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setSpacing(8);
    buttonsLayout->addStretch(); // Push buttons to the right

    hintButton = new QPushButton(tr("Hint"), this);
    checkButton = new QPushButton(tr("Check"), this);

    connect(hintButton, &QPushButton::clicked, this, &SudokuBoard::onHintClicked);
    connect(checkButton, &QPushButton::clicked, this, &SudokuBoard::onCheckClicked);

    hintButton->setDisabled(true);
    checkButton->setCheckable(true);

    hintButton->setObjectName("hintButton");
    checkButton->setObjectName("checkButton");

    hintButton->setFocusPolicy(Qt::StrongFocus);
    checkButton->setFocusPolicy(Qt::StrongFocus);

    buttonsLayout->addWidget(hintButton);
    buttonsLayout->addWidget(checkButton);

    root->addLayout(grid);
    root->addLayout(buttonsLayout);

    all_cells[0][0]->setFocus();
    setAxisHighlight(0, 0);

    applyButtonStyles();
    initializePuzzle(numberOfGivenCells); // Set up the initial Sudoku puzzle
}

/**
 * @brief Slot called when a cell is activated (focused or clicked).
 */
void SudokuBoard::onCellActivated(int r, int c) {
    currentActiveRow = r;
    currentActiveCol = c;

    setAxisHighlight(r, c);

    if(r == -1 || c == -1 || all_cells[r][c]->isReadOnly()){
        hintButton->setDisabled(true);
    } else {
        hintButton->setDisabled(false);
    }
}

/**
 * @brief Highlight the row and column of the selected cell.
 */
void SudokuBoard::setAxisHighlight(int r, int c) {
    if(r == -1 || c == -1) return;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            auto *cell = all_cells[i][j];
            bool isAxis = (i == r) || (j == c);
            bool isSelected = (i == r) && (j == c) && cell->hasFocus();
            cell->setProperty("axis", isAxis);
            cell->setProperty("selected", isSelected);

            // Re-apply styles to reflect property changes
            cell->style()->unpolish(cell);
            cell->style()->polish(cell);
        }
    }
}

/**
 * @brief Apply styles to the buttons.
 */
void SudokuBoard::applyButtonStyles() {
    QString style = R"(
        QPushButton#hintButton,
        QPushButton#checkButton {
            color: #1a202c;
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ffffff, stop:1 #e2e8f0);
            border: 1px solid #cbd5e0;
            border-radius: 6px;
            padding: 6px 16px;
            font: 600 14px "Segoe UI";
        }

        QPushButton#checkButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f0fff4, stop:1 #c6f6d5);
        }

        QPushButton#hintButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #fffaf0, stop:1 #fefcbf);
        }

        QPushButton#hintButton:hover,
        QPushButton#checkButton:hover {
            border-color: #a0aec0;
        }

        QPushButton#checkButton:pressed {
            border: 1px solid #38a169;
            box-shadow: 0 0 0 2px rgba(56,161,105,0.4);
            background: #e2e8f0;
        }

        QPushButton#hintButton:pressed {
            border: 1px solid #ecc94b;
            box-shadow: 0 0 0 2px rgba(236,201,75,0.4);
            background: #e2e8f0;
        }

        QPushButton#checkButton:focus {
            outline: none;
            border: 1px solid #38a169;
            box-shadow: 0 0 0 2px rgba(56,161,105,0.4);
        }

        QPushButton#hintButton:focus {
            outline: none;
            border: 1px solid #ecc94b;
            box-shadow: 0 0 0 2px rgba(236,201,75,0.4);
        }

        QPushButton#checkButton:disabled,
        QPushButton#hintButton:disabled {
            color: #718096;
            background: #edf2f7;
            border-color: #e2e8f0;
        }

        /* Active (checked) state for Check button: darker green and white text */
        QPushButton#checkButton:checked {
            color: #ffffff;
            border: 2px solid #2f855a;
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #68d391, stop:1 #38a169);
        }

        QPushButton#checkButton:checked:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #48bb78, stop:1 #2f855a);
        }

        QPushButton#checkButton:checked:pressed {
            background: #2f855a;
        }
    )";
    setStyleSheet(style);
}

// Helper functions for Sudoku generation and validation

/**
 * @brief Initialize the Sudoku puzzle by generating a solved grid and then removing numbers to create the puzzle.
 * 
 * @param numberOfGivenCells The number of cells to keep as given values in the puzzle.
 */
void SudokuBoard::initializePuzzle(int numberOfGivenCells) {
    generateSolvedSudoku(solvedSudoku);

    auto puzzle = createPuzzleFromSolution(solvedSudoku, numberOfGivenCells);

    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (puzzle[r][c] != 0) {
                all_cells[r][c]->setAsGivenCell(puzzle[r][c]);
            }
        }
    }
}

/**
 * @brief Check if placing a number in a specific cell is valid according to Sudoku rules.
 * 
 * @param grid The current Sudoku grid.
 * @param row The row index of the cell.
 * @param col The column index of the cell.
 * @param num The number to place in the cell.
 * @return true if placing the number is valid, false otherwise.
 */
bool SudokuBoard::isValidForGrid(const std::array<std::array<int, 9>, 9>& grid, int row, int col, int num) const {
    // Check row
    for (int c = 0; c < 9; ++c) {
        if (c != col && grid[row][c] == num) {
            return false;
        }
    }
    
    // Check column
    for (int r = 0; r < 9; ++r) {
        if (r != row && grid[r][col] == num) {
            return false;
        }
    }
    
    // Check 3x3 box
    int boxStartRow = (row / 3) * 3;
    int boxStartCol = (col / 3) * 3;
    for (int r = boxStartRow; r < boxStartRow + 3; ++r) {
        for (int c = boxStartCol; c < boxStartCol + 3; ++c) {
            if ((r != row || c != col) && grid[r][c] == num) {
                return false;
            }
        }
    }
    
    return true;
}

/**
 * @brief Generate a fully solved Sudoku grid using backtracking with randomization.
 * 
 * @param grid The grid to fill with a valid Sudoku solution.
 */
void SudokuBoard::generateSolvedSudoku(std::array<std::array<int, 9>, 9>& grid) const {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            grid[i][j] = 0;
        }
    }
    
    fillGridRandomly(grid, 0, 0);
}

/**
 * @brief Recursively fill the Sudoku grid using backtracking with randomization.
 * 
 * @param grid The Sudoku grid to fill.
 * @param row The current row index.
 * @param col The current column index.
 * @return true if the grid was successfully filled, false otherwise.
 */
bool SudokuBoard::fillGridRandomly(std::array<std::array<int, 9>, 9>& grid, int row, int col) const {
    // Move to next row if at end of current row
    if (col == 9) {
        return fillGridRandomly(grid, row + 1, 0);
    }
    
    if (row == 9) {
        return true; // Successfully filled the grid
    }
    
    // Skip if cell is already filled
    if (grid[row][col] != 0) {
        return fillGridRandomly(grid, row, col + 1);
    }
    
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::shuffle(numbers.begin(), numbers.end(), rng);
    
    for (int num : numbers) {
        if (isValidForGrid(grid, row, col, num)) {
            grid[row][col] = num;
            
            if (fillGridRandomly(grid, row, col + 1)) return true;
            
            grid[row][col] = 0;
        }
    }
    
    return false;
}

/**
 * @brief Count the number of solutions for a given Sudoku grid using backtracking.
 * 
 * @param grid The Sudoku grid to evaluate.
 * @return Returns 1 if there is a unique solution, more than 1 if multiple solutions exist, or 0 if no solution exists.
 */
int SudokuBoard::countSolutions(std::array<std::array<int, 9>, 9> grid) const {
    int solutions = 0;
    
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (grid[row][col] == 0) {
                for (int num = 1; num <= 9; ++num) {
                    if (isValidForGrid(grid, row, col, num)) {
                        grid[row][col] = num;
                        solutions += countSolutions(grid);
                        grid[row][col] = 0;
                        if (solutions > 1) return solutions; // Early exit
                    }
                }
                return solutions;
            }
        }
    }
    return 1;
}

/**
 * @brief Create a Sudoku puzzle by removing numbers from a solved grid while ensuring a unique solution.
 * 
 * @param solution The fully solved Sudoku grid.
 * @return A Sudoku puzzle grid with some numbers removed.
 */
std::array<std::array<int, 9>, 9> SudokuBoard::createPuzzleFromSolution(const std::array<std::array<int, 9>, 9>& solution, int numberOfGivenCells) const {
    auto puzzle = solution;
    
    std::vector<std::pair<int, int>> positions;
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            positions.emplace_back(r, c);
        }
    }
    
    // Shuffle positions for random removal
    std::shuffle(positions.begin(), positions.end(), rng);

    // Remove numbers, keeping exactly numberOfGivenCells given values
    int toRemove = 81 - numberOfGivenCells;
    int removed = 0;
    
    for (const auto& pos : positions) {
        if (removed >= toRemove) break;
        
        int row = pos.first;
        int col = pos.second;
        int original = puzzle[row][col];
        
        puzzle[row][col] = 0;
        
        if (countSolutions(puzzle) == 1) {
            removed++;
        } else {
            puzzle[row][col] = original;
        }
    }
    
    return puzzle;
}


// Button Clicked Handlers

/**
 * @brief Called when the Hint button is clicked.
 */
void SudokuBoard::onHintClicked() {
    int correctValue = solvedSudoku[currentActiveRow][currentActiveCol];
    all_cells[currentActiveRow][currentActiveCol]->setText(QString::number(correctValue));
}

/**
 * @brief Called when the Check button is clicked.
 */
void SudokuBoard::onCheckClicked() {
    // Reflect the current toggle state of the button
    checkActive = checkButton->isChecked();

    for(int r = 0; r < 9; ++r){
        for(int c = 0; c < 9; ++c){
            if(all_cells[r][c]->isReadOnly()) continue;
            if(!checkActive){
                all_cells[r][c]->hideCheck();
                continue;
            }

            int val = all_cells[r][c]->text().toInt();
            if(val == solvedSudoku[r][c]){
                all_cells[r][c]->setAsCorrect();
            } else {
                all_cells[r][c]->setAsIncorrect();
            }
        }
    }
}
