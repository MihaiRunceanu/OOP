#include "wishlist.h"

void WishList::add_wishlist(const Oferta &o) {
    wishlist_oferte.push_back(o);
}

void WishList::deleteOferte() {
    wishlist_oferte.clear();
}
