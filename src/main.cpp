// Qt
#include <QApplication>
#include <QVBoxLayout>

// STL
#include <array>

// Include
#include "SudokuBoard.h"

int main(int argc, char *argv[]) {
    int numberOfGivenCells = 50;

    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Sudoku");

    auto *root = new QVBoxLayout(&window);
    root->setContentsMargins(16, 16, 16, 16);
    root->setSpacing(10);

    auto *board = new SudokuBoard(&window, numberOfGivenCells);
    root->addWidget(board, 0, Qt::AlignCenter);

    // Set background to white
    window.setStyleSheet(R"(
        QWidget { background: #f7fafc; }
    )");

    window.show();
    return app.exec();
}