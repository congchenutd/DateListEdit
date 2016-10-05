#ifndef DATELISTLINEEDIT_H
#define DATELISTLINEEDIT_H

#include <QLineEdit>
#include <QValidator>

/**
 * A lineedit for a list of dates, e.g., "01/02/2016, 02/29/2017"
 */
class DateListLineEdit : public QLineEdit
{
public:
    DateListLineEdit(const QString& format, const QChar& placeholder,
                     const QChar& separator, QWidget* parent = 0);

protected:
    void keyPressEvent(QKeyEvent* event);

private:
    void installInputMask();

private:
    QString _mask;          // mask for each date section
    QChar   _placeholder;
    QChar   _separator;
    QStringList _masks;
};

/**
 * Validate if an input string such as "01/02/2016, 02/29/201_" is a valid list of dates,
 * for which format is "MM/dd/yyyy", placeholder is '_', and separator is ','
 */
class DateValidator: public QValidator
{
public:
    DateValidator(const QString& format, const QChar& placeholder, const QChar& separator);

    State validate(QString& input, int& pos) const;

private:
    QString _format;
    QChar   _placeholder;
    QChar   _separator;
};


#endif // DATELISTLINEEDIT_H
