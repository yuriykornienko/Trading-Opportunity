#include "FaP.h"

double fairprice(double basicprice, double stavkacb, int period)
{

	double  fairpricefuture = basicprice * (1 + stavkacb * period / 365);
	fairpricefuture = std::ceil(fairpricefuture * 100.0) / 100.0;
	return fairpricefuture;
}

pair<double, double> deltaprice_and_future(double stock_price, int day, double future_price)
{

	double deltapricefuture;
	double deltafuture = (future_price / (stock_price));
	if (deltafuture > 1) {
		deltapricefuture = (deltafuture - 1) * 100;
	}
	if (deltafuture < 1)
	{
		deltapricefuture = (1 - deltafuture) * 100;
	};

	if (deltafuture == 0) {
		deltapricefuture = 0;
	}
	deltapricefuture = std::ceil(deltapricefuture * 100.0) / 100.0;
	double yeld_in_year;
	if (day == 0)
	{
		yeld_in_year = deltapricefuture * 365;
	}
	else
	{
		yeld_in_year = deltapricefuture * (365 / day);
	}

	pair <double, double> pair_rezult;
	pair_rezult = make_pair(deltapricefuture, yeld_in_year);
	return pair_rezult;
}
