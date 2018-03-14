#include "cartWall.h"

CartWall::CartWall(QWidget *parent, int cartWallId)
    : QWidget(parent),
      cartWallId_(cartWallId)
{
    gridLayout_= new QGridLayout(this);

    for (uint32_t x = 0; x < 4; x++) {
        std::vector<CartButton *>buttonRow;
        for (uint32_t y = 0; y < 4; y++) {
            QString title = "";

            auto btn = new CartButton(this, title,
                                      QString::number(x + y, 10));

            btn->setEnabled(false);

            buttonRow.push_back(btn);

            gridLayout_->addWidget(btn, x, y);
        }
        buttons.push_back(buttonRow);
    }

    setLayout(gridLayout_);
}
