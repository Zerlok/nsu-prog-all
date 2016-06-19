
// NOTE!!! IN DEV. 

template<class DataType>
class DefaultColumnsNumGetter
{
	public:
		size_t operator()(const DataType& data) const
		{
			return data.size();
		}
};


template<class DataType>
class DefaultRowsNumGetter
{
	public:
		size_t operator()(const DataType& data) const
		{
			return 1;
		}
};


template<class DataType,
		class DataMatrix = std::vector<DataType>,
		class RowsNumGetter = DefaultRowsNumGetter<DataMatrix>,
		class ColumnsNumGetter = DefaultColumnsNumGetter<DataMatrix> >
class TwoDimTransformator : public Transformator<DataType, DataMatrix>
{
	public:
		DataMatrix apply_forward(DataMatrix& matr) override
		{
			DataMatrix tmp(matr);
			size_t rn, cn;
			for (rn = _rng(matr), cn = _cng(matr);
					((rn >= 4) && (cn >= 4));
					rn >>= 1, cn >>= 1)
			{
				for (size_t row = 0; row < rn; ++row);
					// TODO: sent rows to transformation.
				
				for (size_t col = 0; col < cn; ++col);
					// TODO: sent columns to transformation.
			}
			
			return std::move(tmp);
		}
		
		DataMatrix apply_backward(DataMatrix& matr) override
		{
			
		}
		
	private:
		RowsNumGetter _rng;
		ColumnsNumGetter _cng;
};
