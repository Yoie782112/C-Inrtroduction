#pragma once

namespace gs {

	template <typename T, size_t M, size_t N> class GsMatrix
	{
	public:

		GsMatrix();

		GsMatrix<T, M, N>& operator=(const GsMatrix<T, M, N>& rhs);

		// Matrix mathematical operations                                                                                                                                                                                               
		GsMatrix<T, M, N> operator+(const GsMatrix<T, M, N>& rhs);
		GsMatrix<T, M, N> operator-(const GsMatrix<T, M, N>& rhs);
		template<size_t O>
		GsMatrix<T, M, O> operator*(const GsMatrix<T, N, O>& rhs);

		GsMatrix<T, M, N>& operator+=(const GsMatrix<T, M, N>& rhs);
		GsMatrix<T, M, N>& operator-=(const GsMatrix<T, M, N>& rhs);
		template<size_t O>
		GsMatrix<T, M, O>& operator*=(const GsMatrix<T, N, O>& rhs);

		GsMatrix<T, N, M> transpose();

		// Matrix/scalar operations                                                                                                                                                                                                     
		GsMatrix<T, M, N> operator+(const T& rhs);
		GsMatrix<T, M, N> operator-(const T& rhs);
		GsMatrix<T, M, N> operator*(const T& rhs);
		GsMatrix<T, M, N> operator/(const T& rhs);

		// Access the individual elements                                                                                                                                                                                               
		T& operator()(const unsigned& row, const unsigned& col);
		const T& operator()(const unsigned& row, const unsigned& col) const;

	private:

		T m_mat[M][N];

	};


	template <typename T, size_t M, size_t N>
	GsMatrix<T, M, N>::GsMatrix()
	{
		// init the matrix to zero

		for (unsigned i = 0; i < M; i++) {
			for (unsigned j = 0; j < N; j++) {
				m_mat[i][j] = 0;
			}
		}
		//TODO
	}

	// Assignment Operator                                                                                                                                                        
	template <typename T, size_t M, size_t N>
	GsMatrix<T, M, N>& GsMatrix<T, M, N>::operator=(const GsMatrix<T, M, N>& rhs) {
		if (&rhs == this)
			return *this;
		

		for (unsigned i = 0; i< M; i++) {
			for (unsigned j = 0; j< N; j++) {
				m_mat[i][j] = rhs(i, j);
			}
		}
		return *this;
	}


	// Addition of two matrices                                                                                                                                                   
	template <typename T, size_t M, size_t N>
	GsMatrix<T, M, N> GsMatrix<T, M, N>::operator+(const GsMatrix<T, M, N>& rhs)
	{
		GsMatrix<T, M, N> result;

		for (unsigned i = 0; i< M; i++) {
			for (unsigned j = 0; j< N; j++) {
				result(i, j) = this->m_mat[i][j] + rhs(i, j);
			}
		}

		return result;
	}
	// Subtraction of this matrix and another                                                                                                                                     
	template <typename T, size_t M, size_t N>
	GsMatrix<T, M, N> GsMatrix<T, M, N>::operator-(const GsMatrix<T, M, N>& rhs)
	{
		GsMatrix<T, M, N> result;

		for (unsigned i = 0; i< M; i++) {
			for (unsigned j = 0; j< N; j++) {
				result(i, j) = this->m_mat[i][j] - rhs(i, j);
			}
		}

		return result;
	}

	// Left multiplication of this matrix and another                                                                                                                              
	template <typename T, size_t M, size_t N>
	template<size_t O>
	GsMatrix<T, M, O> GsMatrix<T, M, N>::operator*(const GsMatrix<T, N, O>& rhs)
	{
		GsMatrix<T, M, O> result;
		for (unsigned i = 0; i< M; i++) {
			for (unsigned j = 0; j< N; j++) {
				for (unsigned k = 0; k< M; k++) {
					result(i, j) += this->m_mat[i][k] * rhs(k, j);
				}
			}
		}
		return result;
	}



	// Cumulative addition of this matrix and another                                                                                                                             
	template <typename T, size_t M, size_t N>
	GsMatrix<T, M, N>& GsMatrix<T, M, N>::operator+=(const GsMatrix<T, M, N>& rhs) {	
		for (unsigned i = 0; i< M; i++) {
			for (unsigned j = 0; j< N; j++) {
				this->m_mat[i][j] += rhs(i, j);
			}
		}

		return *this;
	}

	// Cumulative subtraction of this matrix and another                                                                                                                          
	template <typename T, size_t M, size_t N>
	GsMatrix<T, M, N>& GsMatrix<T, M, N>::operator-=(const GsMatrix<T, M, N>& rhs) {
		for (unsigned i = 0; i< M; i++) {
			for (unsigned j = 0; j< N; j++) {
				this->m_mat[i][j] -= rhs(i, j);
			}
		}

		return *this;
	}

	// Cumulative left multiplication of this matrix and another                                                                                                                  
	template <typename T, size_t M, size_t N>
	template<size_t O>
	GsMatrix<T, M, O>& GsMatrix<T, M, N>::operator*=(const GsMatrix<T, N, O>& rhs)
	{
		GsMatrix<T, M, O> result = (*this) * rhs;
		(*this) = result;
		return *this;
	}

	// Calculate a transpose of this matrix                                                                                                                                       
	template <typename T, size_t M, size_t N>
	GsMatrix<T, N, M> GsMatrix<T, M, N>::transpose() {
		GsMatrix<T, N, M> result;
		for (unsigned i = 0; i< M; i++) {
			for (unsigned j = 0; j< N; j++) {
				result(i, j) = this->m_mat[j][i];
			}
		}

		return result;
	}

	// Matrix/scalar addition                                                                                                                                                     
	template <typename T, size_t M, size_t N>
	GsMatrix<T, M, N> GsMatrix<T, M, N>::operator+(const T& rhs) {
		GsMatrix<T, M, N> result;

		for (unsigned i = 0; i< M; i++) {
			for (unsigned j = 0; j< N; j++) {
				result(i, j) = this->m_mat[i][j] + rhs;
			}
		}

		return result;
	}

	// Matrix/scalar subtraction                                                                                                                                                  
	template <typename T, size_t M, size_t N>
	GsMatrix<T, M, N> GsMatrix<T, M, N>::operator-(const T& rhs) {
		GsMatrix<T, M, N> result;

		for (unsigned i = 0; i< M; i++) {
			for (unsigned j = 0; j< N; j++) {
				result(i, j) = this->m_mat[i][j] - rhs;
			}
		}

		return result;
	}

	// Matrix/scalar multiplication                                                                                                                                               
	template <typename T, size_t M, size_t N>
	GsMatrix<T, M, N> GsMatrix<T, M, N>::operator*(const T& rhs) {
		GsMatrix<T, M, N> result;

		for (unsigned i = 0; i< M; i++) {
			for (unsigned j = 0; j< N; j++) {
				result(i, j) = this->m_mat[i][j] * rhs;
			}
		}

		return result;
	}

	// Matrix/scalar division                                                                                                                                                     
	template <typename T, size_t M, size_t N>
	GsMatrix<T, M, N> GsMatrix<T, M, N>::operator/(const T& rhs) {
		GsMatrix<T, M, N> result;

		for (unsigned i = 0; i< M; i++) {
			for (unsigned j = 0; j< N; j++) {
				result(i, j) = this->m_mat[i][j] / rhs;
			}
		}

		return result;
	}


	// Access the individual elements                                                                                                                                             
	template <typename T, size_t M, size_t N>
	T& GsMatrix<T, M, N>::operator()(const unsigned& row, const unsigned& col) {
		return this->m_mat[row][col];
	}

	// Access the individual elements (const)                                                                                                                                     
	template <typename T, size_t M, size_t N>
	const T& GsMatrix<T, M, N>::operator()(const unsigned& row, const unsigned& col) const {
		return this->m_mat[row][col];
	}

	


} // gs
