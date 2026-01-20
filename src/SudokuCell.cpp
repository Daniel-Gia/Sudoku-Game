#include "SudokuCell.h"

/**
 * @brief Constructor
 * @param r Row index
 * @param c Column index
 * @param parent Parent widget
 */
SudokuCell::SudokuCell(int r, int c, QWidget *parent) : QLineEdit(parent), cell_row(r), cell_col(c) {
    setAlignment(Qt::AlignCenter);
    setMaxLength(1);
    setFont(QFont(QStringLiteral("Segoe UI"), 18, QFont::Medium));
    setFixedSize(52, 52);
    setFrame(false);

    // Make sure only digits 1-9 can be entered
    auto rx = QRegularExpression(QStringLiteral("^[1-9]?$"));
    setValidator(new QRegularExpressionValidator(rx, this));

    setProperty("axis", false);
    setProperty("selected", false);
    setProperty("correct", false);
    setProperty("incorrect", false);
    setCursor(Qt::IBeamCursor);
    setContextMenuPolicy(Qt::NoContextMenu);

    QPalette pal = palette();
    pal.setColor(QPalette::Base, Qt::white);
    setPalette(pal);

    setCellStyle();
}

/**
 * @brief Get row index
 * @return Row index
 */
int SudokuCell::row() const { return cell_row; }

/**
 * @brief Get column index
 * @return Column index
 */
int SudokuCell::col() const { return cell_col; }


/**
 * @brief Set as read-only with initial value
 * @param value Initial value to set (the correct answer)
 */
void SudokuCell::setAsGivenCell(int value) {
    setText(QString::number(value));
    setReadOnly(true);
    setProperty("given", true);
    setCellStyle();
}

/**
 * @brief Set cell as correct (answered correctly)
 */
void SudokuCell::setAsCorrect() {
    setProperty("correct", true);
    setCellStyle();
}

/**
 * @brief Set cell as incorrect (answered incorrectly)
 */
void SudokuCell::setAsIncorrect() {
    setProperty("incorrect", true);
    setCellStyle();
}

/**
 * @brief Hide the correct/incorrect check styling
 */
void SudokuCell::hideCheck() {
    setProperty("correct", false);
    setProperty("incorrect", false);
    setCellStyle();
}

/**
 * @brief Focus in event handler
 */
void SudokuCell::focusInEvent(QFocusEvent *e) {
    QLineEdit::focusInEvent(e);
    emit activated(cell_row, cell_col);
}

/**
 * @brief Mouse press event handler
 */
void SudokuCell::mousePressEvent(QMouseEvent *e) {
    QLineEdit::mousePressEvent(e);
    setFocus(Qt::MouseFocusReason);
    emit activated(cell_row, cell_col);
}

/**
 * @brief Set cell style based on its properties (given, correct, incorrect, etc.)
 */
void SudokuCell::setCellStyle() {
    // Determine border widths based on position in the 3x3 grid (some borders are thicker)
    int top = (cell_row % 3 == 0) ? 2 : 1;
    int left = (cell_col % 3 == 0) ? 2 : 1;
    int bottom = (cell_row == 8) ? 2 : ((cell_row % 3 == 2) ? 2 : 1);
    int right = (cell_col == 8) ? 2 : ((cell_col % 3 == 2) ? 2 : 1);
    QString style = QString(
        "QLineEdit {"
        " background: #ffffff;"
        " selection-background-color: #cde7ff;"
        " border-top: %1px solid #4a5568;"
        " border-left: %2px solid #4a5568;"
        " border-bottom: %3px solid #4a5568;"
        " border-right: %4px solid #4a5568;"
        " border-radius: 0;"
        " }"
        " QLineEdit[axis=\"true\"] { background: #eaf4ff; }"
        " QLineEdit[selected=\"true\"] { background: #d6ecff; }"
        " QLineEdit[correct=\"true\"] { background: rgba(56, 178, 72, 0.25); }"
        " QLineEdit[incorrect=\"true\"] { background: rgba(220, 38, 38, 0.25); }"
        " QLineEdit[given=\"true\"] { background: #f7fafc; color: #2d3748; font-weight: bold; }"
    ).arg(top).arg(left).arg(bottom).arg(right);
    setStyleSheet(style);
}
