#include "wtr.h"


void OneDimTransformator::apply_forward(Floats& vec)
{
//	const size_t n = vec.size();

//	if (n < 4)
//		return;

//	Floats wksp = vec;
//	for (size_t nn = n; nn >= 4; nn >>= 1)
//		_tr->forward(wksp);
//	wksp.swap(vec);

	_tr->forward(vec);
}


void OneDimTransformator::apply_backward(Floats& vec)
{
//	const size_t n = vec.size();

//	if (n < 4)
//		return;

//	Floats wksp = vec;
//	for (size_t nn = 4; nn <= n; nn <<= 1)
//		_tr->backward(wksp);

//	wksp.swap(vec);

	_tr->backward(vec);
}


const double DAUB4Transform::c0 = 0.4829629131445341;
const double DAUB4Transform::c1 = 0.8365163037378079;
const double DAUB4Transform::c2 = 0.2241438680420134;
const double DAUB4Transform::c3 = -0.1294095225512604;


void DAUB4Transform::forward(Floats& vec) const
{
	size_t n = vec.size();

	if (n < 4)
		return;

	size_t nh = n - 1;
	Floats wksp = Floats(n);
	size_t i, j;

	for (i = 0, j = 0;
		 j < n - 3;
		 i += 1, j += 2)
	{
		wksp[i] = c0*vec[j] + c1*vec[j+1] + c2*vec[j+2] + c3*vec[j+3];
		wksp[nh-i] = c3*vec[j] - c2*vec[j+1] + c1*vec[j+2] - c0*vec[j+3];
	}

	wksp[i] = c0*vec[n-2] + c1*vec[n-1] + c2*vec[0] + c3*vec[1];
	wksp[nh-i] = c3*vec[n-2] - c2*vec[n-1] + c1*vec[0] - c0*vec[1];

	vec.swap(wksp);
}


void DAUB4Transform::backward(Floats& vec) const
{
	size_t n = vec.size();

	if (n < 4)
		return;

	size_t nh = n - 1;
	size_t nh1 = (nh >> 1) + 1;
	Floats wksp = Floats(n);
	size_t i, j;

	wksp[0] = c2*vec[nh-1] + c1*vec[nh] + c0*vec[0] + c3*vec[nh1-1];
	wksp[1] = c3*vec[nh-1] - c0*vec[nh] + c1*vec[0] - c2*vec[nh1-1];

	for (i = 0, j = 2; i < nh; i++)
	{
		wksp[j++] = c2*vec[i] + c1*vec[nh-i] + c0*vec[i+1] + c3*vec[nh1-i];
		wksp[j++] = c3*vec[i] - c0*vec[nh-i] + c1*vec[i+1] - c2*vec[nh1-i];
	}

	vec.swap(wksp);
}


void PartlyTransform::forward(Floats& vec) const
{
	size_t n = vec.size();

	if (n < 4)
		return;

	Floats wksp = Floats(n, 0.0);
	unsigned long nmod = _wfilt.ncof * n;
	unsigned long n1 = n - 1;
	unsigned long nh = n >> 1;

	unsigned long i, ii;
	for (ii = 0, i = 0;
		 i < n;
		 i += 2, ii++)
	{
		unsigned long ni = i + nmod + _wfilt.ioff;
		unsigned long nj = i + nmod + _wfilt.joff;

		for (int k = 1; k <= _wfilt.ncof; ++k)
		{
			unsigned long jf = n1 & (ni + k);
			unsigned long jr = n1 & (nj + k);
			wksp[ii] += _wfilt.cc[k] * vec[jf+1];
			wksp[ii+nh] += _wfilt.cr[k] * vec[jr+1];
		}
	}

	vec.swap(wksp);
}


void PartlyTransform::backward(Floats& vec) const
{
	size_t n = vec.size();

	if (n < 4)
		return;

	Floats wksp = Floats(n, 0.0);
	unsigned long nmod = _wfilt.ncof * n;
	unsigned long n1 = n - 1;
	unsigned long nh = n >> 1;

	unsigned long i, ii;
	for (ii = 0, i = 0;
		 i < n;
		 i += 2, ii += 1)
	{
		float a_ii = vec[ii];
		float a_ii1 = vec[ii+nh];
		unsigned long ni = i + nmod + _wfilt.ioff;
		unsigned long nj = i + nmod + _wfilt.joff;

		for (int k = 1; k <= _wfilt.ncof; ++k)
		{
			unsigned long jf = (n1 & (ni+k)) + 1;
			unsigned long jr = (n1 & (nj+k)) + 1;
			wksp[jf] += _wfilt.cc[k] * a_ii;
			wksp[jr] += _wfilt.cr[k] * a_ii1;
		}
	}

	vec.swap(wksp);
}


const Floats PartlyTransform::Filt::c4 = {
		0.4829629131445341,
		0.8365163037378079,
		0.2241438680420134,
		-0.1294095225512604
};
const Floats PartlyTransform::Filt::c4r = Floats(4, 0.0);
const Floats PartlyTransform::Filt::c12 = {
		0.111540743350,
		0.494623890398,
		0.751133908021,
		0.315250351709,
		-0.226264693965,
		-0.129766867567,
		0.097501605587,
		0.027522865530,
		-0.031582039318,
		0.000553842201,
		0.004777257511,
		-0.001077301085
};
const Floats PartlyTransform::Filt::c12r = Floats(12, 0.0);
const Floats PartlyTransform::Filt::c20 = {
		0.026670057901,
		0.188176800078,
		0.527201188932,
		0.688459039454,
		0.281172343661,
		-0.249846424327,
		-0.195946274377,
		0.127369340336,
		0.093057364604,
		-0.071394147166,
		-0.029457536822,
		0.033212674059,
		0.003606553567,
		-0.010733175483,
		0.001395351747,
		0.001992405295,
		-0.000685856695,
		-0.000116466855,
		0.000093588670,
		-0.000013264203
};
const Floats PartlyTransform::Filt::c20r = Floats(20, 0.0);


PartlyTransform::Filt::Filt(const Mode& mode)
{
	ncof = int(mode);
	switch (mode)
	{
		case Mode::first:
			cc = c4;
			cr = c4r;
			break;
		case Mode::second:
			cc = c12;
			cr = c12r;
			break;
		case Mode::third:
			cc = c20;
			cr = c20r;
			break;
		default:
			// TODO: throw exception "unimplemented value n in pwtset"
			break;
	}

	float sig = -1.0;
	for (int k = 0; k < ncof; ++k)
	{
		cr[ncof - k] = sig * cc[k];
		sig = -sig;
	}

	ioff = joff = -(ncof >> 1);
}


PartlyTransform::Filt::Filt(const PartlyTransform::Filt& filt)
	: ncof(filt.ncof),
	  ioff(filt.ioff),
	  joff(filt.joff),
	  cc(filt.cc),
	  cr(filt.cr)
{
}
