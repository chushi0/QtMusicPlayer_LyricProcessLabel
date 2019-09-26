#include "lyricprocesslabel.h"

#include <QCoreApplication>
#include <QPainter>
#include <QPainterPath>

LyricProcessLabel::LyricProcessLabel(QWidget *parent) : QLabel(parent), reachedColor(255, 0, 0), unreachedColor(255, 255, 255)
{
}


void LyricProcessLabel::paintEvent(QPaintEvent *)
{
   QMutexLocker locker(&lock);
   QPainter     painter(this);

   painter.setFont(font());

   QFontMetrics fontMetrics = painter.fontMetrics();

   int widgetWidth  = width();
   int widgetHeight = height();

   int fullWidth = fontMetrics.horizontalAdvance(text);
   int x         = (widgetWidth - fullWidth) / 2;
   int width     = fontMetrics.horizontalAdvance(text.mid(0, start)) + static_cast<int>(fontMetrics.horizontalAdvance(text.mid(start, end - start)) * progress);
   if (x < 0)
   {
      if (width > widgetWidth / 2)
      {
         int mw = -x * 2;
         int m  = width - widgetWidth / 2;
         if (m > mw)
         {
            m = mw;
         }
         painter.translate(-m, 0);
      }
      x = 0;
   }

   QPainterPath path1, path2;
   path1.addRect(QRectF(x, 0, width, widgetHeight));
   path2.addRect(QRectF(x + width, 0, fullWidth - width, widgetHeight));

   painter.setPen(reachedColor);
   painter.setClipPath(path1);
   painter.drawText(x, widgetHeight * 3 / 4, text);

   painter.setPen(unreachedColor);
   painter.setClipPath(path2);
   painter.drawText(x, widgetHeight * 3 / 4, text);

   painter.end();
}


void LyricProcessLabel::setTextAndProgress(const QString& text, const int& start, const int& end, const float& progress)
{
   QMutexLocker locker(&lock);

   this->text     = text;
   this->start    = start;
   this->end      = end;
   this->progress = progress;

   update();
}


void LyricProcessLabel::setReachedColor(const QColor& color)
{
   reachedColor = color;
}


void LyricProcessLabel::setUnreachedColor(const QColor& color)
{
   unreachedColor = color;
}


void LyricProcessLabel::mousePressEvent(QMouseEvent *)
{
   emit clicked();
}
