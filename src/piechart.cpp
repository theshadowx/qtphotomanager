#include "piechart.h"


/// Constructor of PieChart
PieChart::PieChart(QGraphicsItem *parent):
    QGraphicsItem(parent)
{
    jpgCount = 0;
    pngCount = 0;
    bmpCount = 0;

    lowCount = 0;
    averageCount = 0;
    highCount = 0;

    RCount = 0;
    FCount = 0;

    smallCount = 0;
    mediumCount = 0;
    largeCount = 0;

    width = 0;
    height = 0;
}

/// Destructor of PieChart
PieChart::~PieChart()
{
}

/// The bouding rectangle of the pie chart
QRectF PieChart::boundingRect() const
{
    return QRectF(0,0,width,height);
}

/// Painting the pie chart
void PieChart::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    QRectF rectangle = boundingRect();
    painter->fillRect(rectangle,Qt::NoBrush);

    if (parameter == "Type"){ /// Type
        spanAngle=360*16*jpgCount/totalCount;
        painter->setBrush(QColor(160,37,3));
        painter->drawPie(rectangle,0,spanAngle);

        startAngle = spanAngle;
        spanAngle = 360*16*pngCount/totalCount;
        painter->setBrush(QColor(65,70,132));
        painter->drawPie(rectangle,startAngle,spanAngle);

        startAngle += spanAngle;
        spanAngle = 360*16*bmpCount/totalCount;
        painter->setBrush(QColor(136,20,105));
        painter->drawPie(rectangle,startAngle,spanAngle);

    }else if (parameter == "Size"){ /// Size
        spanAngle=360*16*smallCount/totalCount;
        painter->setBrush(QColor(160,37,3));
        painter->drawPie(rectangle,0,spanAngle);

        startAngle = spanAngle;
        spanAngle = 360*16*mediumCount/totalCount;
        painter->setBrush(QColor(136,20,105));
        painter->drawPie(rectangle,startAngle,spanAngle);

        startAngle += spanAngle;
        spanAngle = 360*16*largeCount/totalCount;
        painter->setBrush(QColor(65,70,132));
        painter->drawPie(rectangle,startAngle,spanAngle);

    }else if (parameter == "Confidentiality"){ /// Confidentiality
        spanAngle = 360*16*RCount/totalCount;
        painter->setBrush(QColor(160,37,3));
        painter->drawPie(rectangle,0,spanAngle);
        startAngle = spanAngle;
        spanAngle = 360*16*FCount/totalCount;
        painter->setBrush(QColor(136,20,105));
        painter->drawPie(rectangle,startAngle,spanAngle);
        startAngle=spanAngle+startAngle;

    }else if (parameter == "Price"){ /// Price
        spanAngle=360*16*lowCount/totalCount;
        painter->setBrush(QColor(160,37,3));
        painter->drawPie(rectangle,0,spanAngle);

        startAngle = spanAngle;
        spanAngle = 360*16*averageCount/totalCount;
        painter->setBrush(QColor(136,20,105));
        painter->drawPie(rectangle,startAngle,spanAngle);

        startAngle += spanAngle;
        spanAngle = 360*16*highCount/totalCount;
        painter->setBrush(QColor(65,70,132));
        painter->drawPie(rectangle,startAngle,spanAngle);
    }
}

/// Modify the values of the pie chart
void PieChart::buildAChart(QString param, int total, int var1, int var2, int var3)
{
    totalCount=total;
    parameter=param;

    if (parameter == "Type"){
        jpgCount = var1;
        bmpCount = var2;
        pngCount = var3;

    }else if (parameter == "Size"){
        smallCount = var1;
        mediumCount = var2;
        largeCount = var3;

    }else if (parameter == "Confidentiality"){
        RCount = var1;
        FCount = var2;

    }else if (parameter == "Price"){
        lowCount = var1;
        averageCount = var2;
        highCount = var3;
    }
}

void PieChart::setWidth(const int width)
{
    this->width = width;
}

void PieChart::setHeight(const int height)
{
    this->height = height;
}

void PieChart::setSize(const QSize size)
{
    height = size.width();
    width = size.height();

}
