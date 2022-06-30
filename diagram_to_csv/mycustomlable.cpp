#include "mycustomlable.h"

#include <QEvent>
#include <QMouseEvent>

MyCustomLable::MyCustomLable(QWidget* parent) : QLabel(parent)
{

}


bool MyCustomLable::event(QEvent *myEvent)
{
    QMouseEvent *e;
    switch(myEvent->type())
    {
        case(QEvent::MouseButtonRelease):   // Identify Mouse press Event
        {
            e = (QMouseEvent *)myEvent;

            if(e->button() == Qt::LeftButton)
            {
                emit  myLabelClicked(true,
                                     e->pos().x() ,
                                     e->pos().y()
                                     );
            }
            else
            {
                emit  myLabelClicked(false,
                                     e->pos().x() ,
                                     e->pos().y()
                                     );

            }

            break;
        }
    default:
        break;
//        qDebug() << "other Events";
    }
    return QWidget::event(myEvent);
}
