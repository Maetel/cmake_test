#include "ImageAlg.h"
#include <qimage.h>
#include "eigen.h"
#include "utility.h"

double ImageAlg::NCC(QImage const* input1, QImage const* input2) const
{
	auto const& img1 = *input1;
	auto const& img2 = *input2;

	//skip exception handlings

	double numerator = 0., denominator_l = 0., denominator_r = 0.;
	const int wid = img1.width(), hi = img1.height();
	for (int y = 0; y < hi; ++y)
	{
		for (int x = 0; x < wid; ++x)
		{
			const double val_l = static_cast<double>(qRed(img1.pixel(x, y)));
			const double val_r = static_cast<double>(qRed(img2.pixel(x, y)));
			
			numerator += val_l * val_r;
			denominator_l += val_l * val_l;
			denominator_r += val_r * val_r;
		}
	}

	return numerator / std::sqrt(denominator_l * denominator_r);
}


double ImageAlg::ZNCC(QImage const* input1, QImage const* input2) const
{
	//convert to eigen matrix

	auto const& img1 = *input1;
	auto const& img2 = *input2;

	//skip exception handlings

	//convert to eigen matrix
	const int wid = img1.width(), hi = img1.height();
	MatrixXd bucket1(hi, wid), bucket2(hi, wid);
	{
		_TIMER("Copy :");
		for (int y = 0; y < hi; ++y)
		{
			for (int x = 0; x < wid; ++x)
			{
				const double val_l = static_cast<uchar>(qRed(img1.pixel(x, y)));
				const double val_r = static_cast<uchar>(qRed(img2.pixel(x, y)));

				bucket1(y, x) = val_l;
				bucket2(y, x) = val_r;
			}
		}
	}
	

	const int count = wid * hi;
	double mean1 = bucket1.mean();
	double mean2 = bucket2.mean();
	const auto meanSubed1 = bucket1.array() - mean1;
	const auto meanSubed2 = bucket2.array() - mean2;
	double dev1 = std::sqrt(meanSubed1.square().sum() / count);
	double dev2 = std::sqrt(meanSubed2.square().sum() / count);

	return (meanSubed1.cwiseProduct(meanSubed2).sum()) / (count * dev1 * dev2);
}
