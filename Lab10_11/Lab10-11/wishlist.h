#include "domain.h"
#include <vector>
using namespace std;
class WishList{
private:
    vector <Oferta> wishlist_oferte;
public:
    void deleteOferte();

    void add_wishlist(const Oferta &o);

    vector<Oferta> &get_list() {
        return wishlist_oferte;
    }
};

