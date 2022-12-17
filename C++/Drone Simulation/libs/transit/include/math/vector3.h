#ifndef LIBS_TRANSIT_INCLUDE_MATH_VECTOR3_H_
#define LIBS_TRANSIT_INCLUDE_MATH_VECTOR3_H_

#include <cmath>
#include <iostream>
#include <vector>

/// @brief A class built solely to handle 3D vector mathematics.
class Vector3 {
 public:
  float x = 0;  //!< x-coordinate
  float y = 0;  //!< y-coordinate
  float z = 0;  //!< z-coordinate

  /**
   * @brief Default constructor.
   */
  Vector3();

  /**
   * @brief Parameter constructor.
   *
   * @param[in] x_ x-coordinate
   * @param[in] y_ y-coordinate
   * @param[in] z_ z-coordinate
   */
  Vector3(float x_, float y_, float z_);

  /**
   * @brief Overrides + operator.
   * @param[in] v The Vector3 object you would like to add to this Vector3
   * object
   * @return The Vector3 Object comprised of the sum of the two objects
   */
  Vector3 operator+(const Vector3& v);

  /**
   * @brief Overrides - operator.
   * @param[in] v The Vector3 object you would like to subtract to this Vector3
   * object
   * @return The Vector3 Object comprised of the subtraction of the two objects
   */

  Vector3 operator-(const Vector3& v);
  /**
   * @brief Overrides * operator.
   * @param[in] v The Vector3 object you would like to multiply to this Vector3
   * object
   * @return The Vector3 Object comprised of the multiplication of the two
   * objects
   */
  Vector3 operator*(float m);

  /**
   * @brief Overrides / operator.
   * @param[in] v The Vector3 object you would like to divide to this Vector3
   * object
   * @return The Vector3 Object comprised of the division of the two objects
   */
  Vector3 operator/(float m);
  /**
  * @brief Overrides [] operator
  * @param[in] index The index of the element you would like to access
  * @return The float contained at that index, or a dummy value if the index is
  * invalid
  */
  float& operator[](int index) {
    if (index == 0) {
      return x;
    }
    if (index == 1) {
      return y;
    }
    if (index == 2) {
      return z;
    }

    static float dummyData;
    return dummyData;
  }
  /**
  * @brief Overrides [] operator
  * @param[in] index The index of the element you would like to access
  * @return The float contained at that index, or 0.0 if the index is invalid
  */
  float operator[](int index) const {
    if (index == 0) {
      return x;
    }
    if (index == 1) {
      return y;
    }
    if (index == 2) {
      return z;
    }
    return 0.0;
  }
  /**
  * @brief Calculatees the magnitude of a Vector3 object
  * @return A float of the magnitude of the Vector3 object
  */
  float Magnitude() { return std::sqrt(x * x + y * y + z * z); }
  /**
  * @brief Converts the Vector3 object to a unit vector
  * @return The Vector3 convereted as a unit vector
  */
  Vector3 Unit() { return (*this) / Magnitude(); }
  /**
  * @brief Calculates the distance between two Vector3 objects
  * @param v This is compared and calculated with the Vector3 object that called
  * this function to calculate the distance between them
  * @return A float of the distance between the Vector3 objects
  */
  float Distance(const Vector3& v) {
    return sqrt(pow(v.x - this->x, 2) + pow(v.y - this->y, 2) +
                pow(v.z - this->z, 2));
  }

  /**
   * @brief Prints vector to nicely formatted string
   */
  void Print();
};

#endif  // LIBS_TRANSIT_INCLUDE_MATH_VECTOR3_H_
