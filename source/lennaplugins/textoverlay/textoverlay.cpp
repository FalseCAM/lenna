/**
    This file is part of program Lenna
    Copyright (C) 2013-2016 FalseCAM

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "textoverlay.h"
#include <QtGui/QPainter>
#include "widget.h"

using namespace lenna;
using namespace lenna::plugin::textoverlay;

Textoverlay::Textoverlay() { widget = 0; }

Textoverlay::~Textoverlay() {}

std::string Textoverlay::getName() { return std::string("textoverlay"); }

std::string Textoverlay::getTitle() { return tr("Textoverlay").toStdString(); }

std::string Textoverlay::getVersion() { return std::string("0.1"); }

std::string Textoverlay::getAuthor() { return std::string("FalseCAM"); }

std::string Textoverlay::getDescription() {
  return tr("Plugin to put text onto images").toStdString();
}

QIcon Textoverlay::getIcon() {
  return QIcon(":/plugins/textoverlay/textoverlay");
}

QWidget *Textoverlay::getWidget() {
  if (!this->widget) {
    this->widget = new Widget();
  }
  return this->widget;
}

std::shared_ptr<plugin::Plugin> Textoverlay::getInstance(QString uid) {
  std::shared_ptr<Plugin> plugin = std::shared_ptr<Plugin>(new Textoverlay());
  plugin->setUID(uid);
  return plugin;
}

void Textoverlay::edit(std::shared_ptr<LennaImage> img) {
  getWidget();
  if (widget->isActivated()) {
    int cols = img->getImage().cols;
    int rows = img->getImage().rows;
    QImage *overlay = new QImage(img->getImage().data, img->getImage().cols,
                                 img->getImage().rows, img->getImage().step,
                                 QImage::Format_RGB888);
    QPainter painter(overlay);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    int x = (int)((double)cols * ((double)widget->getX() / 100.0));
    int y = (int)((double)rows * ((double)widget->getY() / 100.0));
    QColor brgColor =
        QColor(widget->getColor()->blue(), widget->getColor()->green(),
               widget->getColor()->red());
    painter.setPen(brgColor);
    QFont tempFont = *widget->getFont();
    tempFont.setPointSize((int)(tempFont.pointSize() * cols / 100));
    painter.setFont(tempFont);
    painter.drawText(x, y, widget->getText());
    painter.end();
  }
}
