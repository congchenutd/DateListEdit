#include "DateListLineEdit.h"

#include <QKeyEvent>
#include <QDate>

// Placeholder can't be space
// Separator can't be ';' which is reversed for input mask
DateListLineEdit::DateListLineEdit(const QString& format, const QChar& placeholder,
                                   const QChar& separator, QWidget* parent)
    : QLineEdit     (parent),
      _placeholder  (placeholder),
      _separator    (separator)
{
    // create date mask from format
    foreach (const QChar& ch, format)
    {
        if (ch == 'y' || ch == 'M' || ch == 'd')
            _mask += '9';
        else
            _mask += ch;
    }
    _masks << _mask;

    installInputMask();
    setValidator(new DateValidator(format, placeholder, separator));
}

void DateListLineEdit::keyPressEvent(QKeyEvent* event)
{
    QLineEdit::keyPressEvent(event);

    // new section
    if (event->text() == _separator)
    {
        _masks << _mask;    // add a new mask to the mask list
        installInputMask();

        // Validator will reset cursor. Move cursor to the new section
        setCursorPosition(displayText().lastIndexOf(_separator));
    }

    // delete a char
    else if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace)
    {
        QStringList dateStrings = text().split(QString(_separator) + " ");
        if (dateStrings.length() > 1)   // don't do anything for the only section
            for (int i = 0; i < dateStrings.length(); ++i)
            {
                QString dateString = dateStrings.at(i);

                // Delete empty section
                if (dateString.count(QRegularExpression("\\d")) == 0)
                {
                    dateStrings.removeAt(i);
                    _masks.removeAt(i);
                    installInputMask();
                    setCursorPosition(displayText().length());
                }
            }
    }
}

void DateListLineEdit::installInputMask() {
    setInputMask(_masks.join(QString(_separator) + " ") + ";" + _placeholder);
}

///////////////////////////////////////////////////////////////////////////
DateValidator::DateValidator(const QString& format, const QChar& placeholder,
                             const QChar& separator)
    : _format       (format),
      _placeholder  (placeholder),
      _separator    (separator)
{}

QValidator::State DateValidator::validate(QString& input, int& pos) const
{
    Q_UNUSED(pos)

    QStringList sections = input.split(_separator);
    foreach (const QString& section, sections)
    {
        QString dateString = section.trimmed();

        // still editing
        if (dateString.contains(_placeholder))
            return Intermediate;

        if (!QDate::fromString(dateString, _format).isValid())
            return Invalid;
    }
    return Acceptable;
}

