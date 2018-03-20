#include "cartWall.h"
#include "cartPageButton.h"

auto constexpr NO_CART_ROWS = 4;
auto constexpr NO_CART_COLS = 5;
auto constexpr LHS_PAGE_COL = 0;
auto constexpr RHS_PAGE_COL = NO_CART_COLS + 1;

CartWall::CartWall(QWidget *parent, int cartWallId)
    : QWidget(parent),
      cartWallId_(cartWallId)
{
    gridLayout_= new QGridLayout(this);

    for (auto x = 0; x < NO_CART_COLS; x++) {
        std::vector<CartButton *>buttonCol;

        for (auto y = 0; y < NO_CART_ROWS; y++) {
            QString title = "";

            auto btn = new CartButton(this, title,
                                      QString::number(x + y, 10));

            btn->setEnabled(false);

            buttonCol.push_back(btn);

            gridLayout_->addWidget(btn, y, x + 1);
        }

        buttons.push_back(buttonCol);
    }

    for (auto page = 0; page < NO_CART_ROWS; page++) {
        auto lhsPageButton = new CartPageButton(this, page);
        auto rhsPageButton = new CartPageButton(this, page + NO_CART_ROWS);

        gridLayout_->addWidget(lhsPageButton, page, LHS_PAGE_COL);
        gridLayout_->addWidget(rhsPageButton, page, RHS_PAGE_COL);
    }

    gridLayout_->setColumnStretch(LHS_PAGE_COL, 1);
    gridLayout_->setColumnStretch(RHS_PAGE_COL, 1);

    for (auto i = 0; i < NO_CART_COLS; i++)
        gridLayout_->setColumnStretch(i + 1, 3);

    setLayout(gridLayout_);
}
