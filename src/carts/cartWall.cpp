#include "cartWall.h"
#include "cartButton.h"

auto constexpr NO_CART_ROWS = 4;
auto constexpr NO_CART_COLS = 5;
auto constexpr LHS_PAGE_COL = 0;
auto constexpr RHS_PAGE_COL = NO_CART_COLS + 1;
auto constexpr NO_PAGES = NO_CART_ROWS * 2;

CartWall::CartWall(AudioManager *audioMan, QWidget *parent, int cartWallId)
    : QWidget(parent),
      cartWallId_(cartWallId)
{
    gridLayout_= new QGridLayout(this);

    for (auto page = 0; page < NO_CART_ROWS; page++) {
        auto lhsPageButton = new CartPageButton(this, page);
        auto rhsPageButton = new CartPageButton(this, page + NO_CART_ROWS);

        gridLayout_->addWidget(lhsPageButton, page, LHS_PAGE_COL);
        gridLayout_->addWidget(rhsPageButton, page, RHS_PAGE_COL);
        pageButtons.push_back(lhsPageButton);
        pageButtons.push_back(rhsPageButton);
    }

    // Connect page change events as page updates to all other buttons
    // so each button is notified when a new button is the current
    // page.
    for (auto pageButton : pageButtons)
        for (auto pb : pageButtons)
            connect(pageButton, &CartPageButton::pageChange,
                    pb, &CartPageButton::pageUpdate);

    // We begin on page 0.
    for (auto pageButton : pageButtons)
        pageButton->pageUpdate(0);

    for (auto x = 0; x < NO_CART_COLS; x++) {
        std::vector<QStackedWidget *>buttonCol;

        for (auto y = 0; y < NO_CART_ROWS; y++) {
            QStackedWidget *buttonStack = createCartButtonStack(audioMan);

            gridLayout_->addWidget(buttonStack, y, x + 1);

            buttonCol.push_back(buttonStack);

            for (auto pageButton : pageButtons)
                connect(pageButton, &CartPageButton::pageChange,
                        buttonStack, &QStackedWidget::setCurrentIndex);
        }

        buttonStacks.push_back(buttonCol);
    }

    gridLayout_->setColumnStretch(LHS_PAGE_COL, 1);
    gridLayout_->setColumnStretch(RHS_PAGE_COL, 1);

    for (auto i = 0; i < NO_CART_COLS; i++)
        gridLayout_->setColumnStretch(i + 1, 3);

    setLayout(gridLayout_);
}

QStackedWidget * CartWall::createCartButtonStack(AudioManager *audioMan)
{
    QStackedWidget *ret = new QStackedWidget(this);

    for (auto page = 0; page < NO_PAGES; page++) {
        auto btn = new CartButton(this, "foo", "bar");

        btn->setEnabled(false);

        ret->addWidget(btn);
    }

    return ret;
}
