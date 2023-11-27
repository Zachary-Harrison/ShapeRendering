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

    // Rotation matrix for x-axis
    Matrix3x3<double> rotX = {
        { 1, 0, 0 },
        { 0, cos(xAngle), -sin(xAngle) },
        { 0, sin(xAngle), cos(xAngle) }
    };

    // Rotation matrix for y-axis
    Matrix3x3<double> rotY = {
        { cos(yAngle), 0, sin(yAngle) },
        { 0, 1, 0 },
        { -sin(yAngle), 0, cos(yAngle) }
    };

    // Rotation matrix for z-axis
    Matrix3x3<double> rotZ = {
        { cos(zAngle), -sin(zAngle), 0 },
        { sin(zAngle), cos(zAngle), 0 },
        { 0, 0, 1 }
    };

    Matrix3x3<double> rot = rotZ * rotY * rotX;

    // Create a new list to store the updated vectors
    std::vector<Vector<P, D>> newData;

    // Rotate the points and their directions (surface normals)
    for (const Vector<P, D>& vector : this->_origData)
    {
        Vector<P, D> newVector;
        newVector.position = rot * vector.position;
        newVector.direction = rot * vector.direction;
        // float sinA = sin(xAngle);
        // float cosA = cos(xAngle);
        // float sinB = sin(yAngle);
        // float cosB = cos(yAngle);
        // float sinC = sin(zAngle);
        // float cosC = cos(zAngle);

        // newVector.position.x = vector.position.y * sinA * sinB * cosC - vector.position.z * cosA * sinB * cosC +
        //                        vector.position.y * cosA * sinC + vector.position.z * sinA * sinC + vector.position.x * cosB * cosC;

        // newVector.position.y = vector.position.y * cosA * cosC + vector.position.z * sinA * cosC -
        //                        vector.position.y * sinA * sinB * sinC + vector.position.z * cosA * sinB * sinC -
        //                        vector.position.x * cosB * sinC;

        // newVector.position.z = vector.position.z * cosA * cosB - vector.position.y * sinA * cosB + vector.position.x * sinB;

        // newVector.direction.x = vector.direction.y * sinA * sinB * cosC - vector.direction.z * cosA * sinB * cosC +
        //                         vector.direction.y * cosA * sinC + vector.direction.z * sinA * sinC + vector.direction.x * cosB * cosC;

        // newVector.direction.y = vector.direction.y * cosA * cosC + vector.direction.z * sinA * cosC -
        //                         vector.direction.y * sinA * sinB * sinC + vector.direction.z * cosA * sinB * sinC -
        //                         vector.direction.x * cosB * sinC;

        // newVector.direction.z = vector.direction.z * cosA * cosB - vector.direction.y * sinA * cosB + vector.direction.x * sinB;

        // Add the updated vector to the new list
        newData.push_back(newVector);
    }

    // Update data
    this->_data = newData;
}