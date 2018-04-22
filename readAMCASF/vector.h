#ifndef _VECTOR_H
#define _VECTOR_H

//������
class vector
{

    // ��
    friend vector    operator-( vector const& );

    // ������
    friend vector    operator+( vector const&, vector const& );

    // subtraction
    friend vector    operator-( vector const&, vector const& );

    // dot product
    friend float    operator%( vector const&, vector const& );
	friend vector   operator%(vector const&,float);

    // cross product
    friend vector    operator*( vector const&, vector const& );

	friend vector	operator+=(vector &,vector const&);

    // scalar Multiplication
    friend vector    operator*( vector const&, float );

    // scalar Division
    friend vector    operator/( vector const&, float );


    friend float    len( vector const& );
    friend vector	normalize( vector const& );

	friend vector       interpolate( float, vector const&, vector const& );

    friend float       angle( vector const&, vector const& );

  // member functions
  public:
    // ���캯�����޲Σ�xyz��������ά�������
    vector() {}
    vector( float x, float y, float z ) { p[0]=x; p[1]=y; p[2]=z; }
    vector( float a[3] ) { p[0]=a[0]; p[1]=a[1]; p[2]=a[2]; }
	//��������
	~vector() {};
    // ��ѯ��������ѯ�±�Ϊ i ���������ݳ�Ա
    float& operator[](int i) { return p[i];}
	//xyz����������Ա��ȡ��������
	float x() const { return p[0]; };
	float y() const { return p[1]; };
	float z() const { return p[2]; };
	//��λ��ȡ��ά���꺯��
	float getValue( int n ) const { return p[n]; }
	//��ȡ��ά���꺯�����������ں������� d[3] ��
    void   getValue( float d[3] ) { d[0]=p[0]; d[1]=p[1]; d[2]=p[2]; }
	//������ά���꺯������������ d[3]�����ݴ�������ݳ�Ա��
    void   setValue( float d[3] ) { p[0]=d[0]; p[1]=d[1]; p[2]=d[2]; }
	//������ά���꺯������������ xyz�����ݴ�������ݳ�Ա��
	vector setValue( float x, float y, float z )
								   { p[0]=x, p[1]=y, p[2]=z; return *this; }
	//���õ����������ݺ������� n Ϊ��λ�±�
	float setValue( int n, float x )
								   { return p[n]=x; }
    //���õ����������ݺ�����xyz�ֿ�
    void set_x( float x ) { p[0]=x; };
    void set_y( float x ) { p[1]=x; };
    void set_z( float x ) { p[2]=x; };
	//���㲢��ȡ��������
	float length() const;



	//=============���ݳ�Ա===============//
    float p[3]; //X, Y, Z components of the vector
};


#endif
