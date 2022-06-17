#include "mycustomlable.h"

#include <QEvent>
#include <QMouseEvent>

MyCustomLable::MyCustomLable(QWidget* parent) : QLabel(parent)
{   
    connect(this, SIGNAL(myLabelClicked(bool,int ,int )),
            this, SLOT(slotLabelClicked(bool,int ,int)));
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
                                     e->position().x() ,
                                     e->position().y()
                                     );
            }
            else
            {
                emit  myLabelClicked(false,
                                     e->position().x() ,
                                     e->position().y()
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
