#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QFont>
#include <QPalette>
#include <QFocusEvent>
#include <QMouseEvent>
#include <QString>

class SudokuCell : public QLineEdit {
    Q_OBJECT
    
    public:
        explicit SudokuCell(int r, int c, QWidget *parent = nullptr);
        int row() const;
        int col() const;
        void setAsGivenCell(int value);
        void setAsCorrect();
        void setAsIncorrect();
        void hideCheck();

    signals:
        void activated(int row, int col); // Emitted when the cell is focused or clicked (to notify SudokuBoard)

    protected:
        void focusInEvent(QFocusEvent *e) override;
        void mousePressEvent(QMouseEvent *e) override;

    private:
        int cell_row;
        int cell_col;
        void setCellStyle();
};
