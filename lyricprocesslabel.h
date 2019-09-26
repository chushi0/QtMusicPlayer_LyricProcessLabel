#pragma once

#include "lyricprocesslabel_global.h"
#include <QLabel>
#include <QMutex>

class LYRICPROCESSLABELSHARED_EXPORT LyricProcessLabel : public QLabel
{
   Q_OBJECT
public:
   explicit LyricProcessLabel(QWidget *parent = nullptr);
   void setTextAndProgress(const QString& text, const int& start, const int& end, const float& progress);
   void setReachedColor(const QColor& color);
   void setUnreachedColor(const QColor& color);

protected:
   void paintEvent(QPaintEvent *);
   void mousePressEvent(QMouseEvent *);

Q_SIGNALS:
   void clicked();

private:
   QString text;
   int start;
   int end;
   float progress;
   QColor reachedColor;
   QColor unreachedColor;

   QMutex lock;
};
