#include "Matrix3x3.hpp"
#include "Shape.hpp"
#include "Triple.hpp"

template <typename P, typename D> // P = PositionType, D = DirectionType
class Cube : public Shape<P, D>
{
  public:
    Cube(P sideLength, Triple<P> center);

    Cube(P sideLength, P initialX, P initialY, P initialZ);

    void update(double xAngle, double yAngle, double zAngle) override;

  private:
    std::vector<Vector<P, D>> _origData;
};

template <typename P, typename D>
Cube<P, D>::Cube(P sideLength, Triple<P> center)
{
    this->setCenter(center);

    static_assert(std::is_arithmetic<P>::value, "Type T must be arithmetic");
    static_assert(std::is_arithmetic<D>::value, "Type R must be arithmetic");
    P halfLen = sideLength / 2;

    // Normals for x faces
    Triple<D> posXNormal{ 1, 0, 0 };
    Triple<D> negXNormal{ -1, 0, 0 };
    for (P y = -halfLen; y <= halfLen; y += 1)
    {
        for (P z = -halfLen; z <= halfLen; z += 1)
        {
            this->_origData.push_back(Vector<P, P>(Triple<P>{ -halfLen, y, z }, posXNormal));
            this->_origData.push_back(Vector<P, P>(Triple<P>{ halfLen, y, z }, negXNormal));
        }
    }

    // Normals for y faces
    Triple<D> posYNormal{ 0, 1, 0 };
    Triple<D> negYNormal{ 0, -1, 0 };
    for (P x = -halfLen; x <= halfLen; x += 1)
    {
        for (P z = -halfLen; z <= halfLen; z += 1)
        {
            this->_origData.push_back(Vector<P, P>(Triple<P>{ x, -halfLen, z }, posYNormal));
            this->_origData.push_back(Vector<P, P>(Triple<P>{ x, halfLen, z }, negYNormal));
        }
    }

    // Normals for z faces
    Triple<D> posZNormal{ 0, 0, 1 };
    Triple<D> negZNormal{ 0, 0, -1 };
    for (P x = -halfLen; x <= halfLen; x += 1)
    {
        for (P y = -halfLen; y <= halfLen; y += 1)
        {
            this->_origData.push_back(Vector<P, P>(Triple<P>{ x, y, -halfLen }, posZNormal));
            this->_origData.push_back(Vector<P, P>(Triple<P>{ x, y, halfLen }, negZNormal));
        }
    }
}

template <typename P, typename D>
Cube<P, D>::Cube(P sideLength, P initialX, P initialY, P initialZ) :
    Cube(sideLength, Triple<P>{ initialX, initialY, initialZ })
{
}

template <typename P, typename D>
void Cube<P, D>::update(double xAngle, double yAngle, double zAngle)
{

    Matrix3x3<double> rotX = Matrix3x3<double>::rotationX(xAngle);
    Matrix3x3<double> rotY = Matrix3x3<double>::rotationY(yAngle);
    Matrix3x3<double> rotZ = Matrix3x3<double>::rotationZ(zAngle);

    Matrix3x3<double> rot = rotZ * rotY * rotX;

    std::vector<Vector<P, D>> newData;
    // Rotate the points and their surface normals
    for (const Vector<P, D>& vector : this->_origData)
    {
        Vector<P, D> newVector;
        newVector.position = rot * vector.position;
        newVector.direction = rot * vector.direction;
        newData.push_back(newVector);
    }

    // Update data
    this->_data = newData;
}