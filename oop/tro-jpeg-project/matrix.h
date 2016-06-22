#ifndef __MATRIX_H__
#define __MATRIX_H__


template<class T>
class Matrix
{
	public:
		using Type = T;
		using Set = std::vector<T>;

		class Row
		{
			public:
				Row() {}
				Row(Matrix* m, const size_t& n)
					: _subdata((m != nullptr ) ? m->cols() : 0),
					  _row_num(n)
				{
					for (size_t i = 0; i < _subdata.size(); ++i)
						_subdata[i] = m->_at(n, i);
				}
				Row(const Matrix* m, const size_t& n)
					: _subdata((m != nullptr) ? m->cols() : 0),
					  _row_num(n)
				{
					for (size_t i = 0; i < _subdata.size(); ++i)
						_subdata[i] = m->_at(n, i);
				}
				Row(const Row& row)
					: _subdata(row._subdata),
					  _row_num(row._row_num) {}
				Row(Row&& row)
					: _subdata(std::move(row._subdata)),
					  _row_num(std::move(row._row_num)) {}
				~Row() {}

				size_t size() const
				{
					return _subdata.size();
				}

				T& operator[](const size_t& i)
				{
					return _subdata[i];
				}

				const T& operator[](const size_t& i) const
				{
					return _subdata[i];
				}

				Row& operator=(const Row& row)
				{
					_subdata = row._subdata;
					_row_num = row._row_num;

					return (*this);
				}

				Row& operator=(Row&& row)
				{
					_subdata = std::move(row._subdata);
					_row_num = std::move(row._row_num);

					return (*this);
				}

				size_t get_num() const
				{
					return _row_num;
				}

			private:
				std::vector<T> _subdata;
				size_t _row_num;
		};

		class Col
		{
			public:
				Col() {}
				Col(Matrix* m, const size_t& n)
					: _subdata((m != nullptr) ? m->rows() : 0),
					  _col_num(n)
				{
					for (size_t i = 0; i < _subdata.size(); ++i)
						_subdata[i] = m->_at(i, n);
				}
				Col(const Matrix* m, const size_t& n)
					: _subdata((m != nullptr) ? m->rows() : 0),
					  _col_num(n)
				{
					for (size_t i = 0; i < _subdata.size(); ++i)
						_subdata[i] = m->_at(i, n);
				}
				Col(const Col& col)
					: _subdata(col._subdata),
					  _col_num(col._col_num) {}
				Col(Col&& col)
					: _subdata(std::move(col._subdata)),
					  _col_num(std::move(col._col_num)) {}
				~Col() {}

				size_t size() const
				{
					return _subdata.size();
				}

				T& operator[](const size_t& i)
				{
					return _subdata[i];
				}

				const T& operator[](const size_t& i) const
				{
					return _subdata[i];
				}

				Col& operator=(const Col& col)
				{
					_subdata = col._subdata;
					_col_num = col._col_num;

					return (*this);
				}

				Col& operator=(Col&& col)
				{
					_subdata = std::move(col._subdata);
					_col_num = std::move(col._col_num);

					return (*this);
				}

				size_t get_num() const
				{
					return _col_num;
				}

			private:
				std::vector<T> _subdata;
				size_t _col_num;
		};

		Matrix(const size_t& rows = 0, const size_t& cols = 0)
			: _data(rows * cols),
			  _rows_num(rows),
			  _cols_num(cols) {}
		Matrix(const Matrix& m)
			: _data(m._data),
			  _rows_num(m._rows_num),
			  _cols_num(m._cols_num) {}
		Matrix(Matrix&& m)
			: _data(std::move(m._data)),
			  _rows_num(std::move(m._rows_num)),
			  _cols_num(std::move(m._cols_num)) {}
		~Matrix() {}

		T& operator[](const size_t& idx)
		{
			return _data[idx];
		}

		const T& operator[](const size_t& idx) const
		{
			return _data[idx];
		}

		T& operator()(const size_t& row_num, const size_t& col_num)
		{
			return _at(row_num, col_num);
		}

		const T& operator()(const size_t& row_num, const size_t& col_num) const
		{
			return _at(row_num, col_num);
		}

		Matrix<T>& operator=(const Matrix<T>& mtrx) = delete;

		Matrix<T>& operator=(Matrix<T>&& mtrx)
		{
			_data = std::move(mtrx._data);
			_rows_num = std::move(mtrx._rows_num);
			_cols_num = std::move(mtrx._cols_num);

			return (*this);
		}

		bool operator==(const Matrix<T>& mtrx) const
		{
			if ((_rows_num != mtrx._rows_num)
					|| (_cols_num != mtrx._cols_num))
				return false;

			for (size_t i = 0; i < size(); ++i)
				if (_data[i] != mtrx._data[i])
					return false;

			return true;
		}

		size_t size() const
		{
			return (_rows_num * _cols_num);
		}

		size_t rows() const
		{
			return _rows_num;
		}

		size_t cols() const
		{
			return _cols_num;
		}

		Row get_row(const size_t& row_num)
		{
			return std::move(Row(this, row_num));
		}

		const Row get_row(const size_t& row_num) const
		{
			return std::move(Row(this, row_num));
		}

		Col get_col(const size_t& col_num)
		{
			return std::move(Col(this, col_num));
		}

		const Col get_col(const size_t& col_num) const
		{
			return std::move(Col(this, col_num));
		}

		void set_row(const Row& row)
		{
			const size_t row_num = row.get_num();
			for (size_t i = 0; i < row.size(); ++i)
				_at(row_num, i) = row[i];
		}

		void set_col(const Col& col)
		{
			const size_t col_num = col.get_num();
			for (size_t i = 0; i < col.size(); ++i)
				_at(i, col_num) = col[i];
		}

	private:
		std::vector<T> _data;
		size_t _rows_num;
		size_t _cols_num;

		T& _at(const size_t& row_num, const size_t& col_num)
		{
			return _data[(row_num * _cols_num) + col_num];
		}

		const T& _at(const size_t& row_num, const size_t& col_num) const
		{
			return _data[(row_num * _cols_num) + col_num];
		}
};


template<class T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& mtrx)
{
	std::cout << "<Matrix len=[" << mtrx.rows() << "x" << mtrx.cols() << "]>" << std::endl;
	for (size_t r = 0; r < mtrx.rows(); ++r)
	{
		const typename Matrix<T>::Row row = mtrx.get_row(r);
		for (size_t i = 0; i < row.size(); ++i)
			std::cout << row[i] << " ";
		std::cout << std::endl;
	}
	std::cout << "</Matrix>" << std::endl;

	return out;
}


// __MATRIX_H__
#endif

