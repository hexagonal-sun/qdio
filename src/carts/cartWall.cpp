#include "cartWall.h"
#include "cartButton.h"

auto constexpr NO_CART_ROWS = 4;
auto constexpr NO_CART_COLS = 5;
auto constexpr LHS_PAGE_COL = 0;
auto constexpr RHS_PAGE_COL = NO_CART_COLS + 1;
auto constexpr NO_PAGES = NO_CART_ROWS * 2;

CartWall::CartWall(AudioManager *audioMan, CartModel *model,
                   enum CartWallType type, QWidget *parent)
    : QWidget(parent),
      model_(model),
      cartWallType_(type)
{
    gridLayout_= new QGridLayout(this);
    enum class pageButtonColumn {
        LHS,
        RHS
    };

    for (const auto pageColumn : {pageButtonColumn::LHS, pageButtonColumn::RHS}) {
        for (auto page = 0; page < NO_CART_ROWS; page++) {
            const auto pageNumber = pageColumn == pageButtonColumn::RHS ?
                        page + NO_CART_ROWS :
                        page;
            const auto gridLayoutColumn = pageColumn == pageButtonColumn::RHS ?
                        RHS_PAGE_COL :
                        LHS_PAGE_COL;

            auto pageButton = new CartPageButton(this, pageNumber);

            gridLayout_->addWidget(pageButton, page, gridLayoutColumn);
            pageButtons.push_back(pageButton);
        }
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

    if (model->isReady())
        createCarts(audioMan);
    else
        connect(model, &CartModel::modelReady,
                std::bind(&CartWall::createCarts, this, audioMan));


    gridLayout_->setColumnStretch(LHS_PAGE_COL, 1);
    gridLayout_->setColumnStretch(RHS_PAGE_COL, 1);

    for (auto i = 0; i < NO_CART_COLS; i++)
        gridLayout_->setColumnStretch(i + 1, 3);

    setLayout(gridLayout_);
}

void CartWall::createCarts(AudioManager *audioMan)
{
    for (auto x = 0; x < NO_CART_COLS; x++) {
        std::vector<QStackedWidget *>buttonCol;

        for (auto y = 0; y < NO_CART_ROWS; y++) {
            QStackedWidget *buttonStack = createCartButtonStack(audioMan, x, y);

            gridLayout_->addWidget(buttonStack, y, x + 1);

            buttonCol.push_back(buttonStack);

            for (auto pageButton : pageButtons)
                connect(pageButton, &CartPageButton::pageChange,
                        buttonStack, &QStackedWidget::setCurrentIndex);
        }

        buttonStacks.push_back(buttonCol);
    }
}

QStackedWidget * CartWall::createCartButtonStack(AudioManager *audioMan,
                                                 unsigned int x, unsigned int y)
{
    QStackedWidget *ret = new QStackedWidget(this);

    for (unsigned int page = 0; page < NO_PAGES; page++) {
        auto btn = model_->getButton(cartWallType_, {x, y, page},
                                     audioMan, this);

        connect(btn, &CartButton::cartPlaybackStrarted,
                pageButtons[page], &CartPageButton::cartPlaybackStarted);

        connect(btn, &CartButton::cartPlaybackStopped,
                pageButtons[page], &CartPageButton::cartPlaybackStopped);

        btn->setEnabled(false);

        ret->addWidget(btn);
    }

    return ret;
}
