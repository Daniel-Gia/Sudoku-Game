#include <array>
#include <random>
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStyle>

class SudokuCell;

class SudokuBoard : public QWidget {
    Q_OBJECT
    
    public:
        explicit SudokuBoard(QWidget *parent = nullptr, int numberOfGivenCells = 50);

    private slots:
        void onCellActivated(int r, int c); // Called when a cell is clicked (called from SudokuCell)

    private:
        std::array<std::array<SudokuCell*, 9>, 9> all_cells{}; //9x9 grid of cells
        std::array<std::array<int, 9>, 9> solvedSudoku{}; // Fully solved Sudoku grid

        QPushButton* hintButton{nullptr};
        QPushButton* checkButton{nullptr};

        int currentActiveRow{0};
        int currentActiveCol{0};
        bool checkActive{false};
        
        mutable std::mt19937 rng{std::random_device{}()}; // Initialize random number generator

        void setAxisHighlight(int r, int c);
        void applyButtonStyles();

        void initializePuzzle(int numberOfGivenCells = 50);
        int countSolutions(std::array<std::array<int, 9>, 9> grid) const;
        bool isValidForGrid(const std::array<std::array<int, 9>, 9>& grid, int row, int col, int num) const;
        void generateSolvedSudoku(std::array<std::array<int, 9>, 9>& grid) const;
        std::array<std::array<int, 9>, 9> createPuzzleFromSolution(const std::array<std::array<int, 9>, 9>& solution, int numberOfGivenCells = 50) const;
        bool fillGridRandomly(std::array<std::array<int, 9>, 9>& grid, int row, int col) const;

        void onHintClicked(); // Hint button clicked
        void onCheckClicked(); // Check button clicked
};
