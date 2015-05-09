/*=========================================================================
 *
 *  Copyright David Doria 2012 daviddoria@gmail.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

/*
KMeans clustering is a method in which to form K (known) clusters of points from
an unorganized set of input points.
*/

#ifndef KMeansClustering_h
#define KMeansClustering_h

// STL
#include <vector>

// Eigen
#include <Eigen/Dense>

class KMeansClustering
{
public:
  typedef Eigen::VectorXf PointType;
  typedef std::vector<PointType, Eigen::aligned_allocator<PointType> > VectorOfPoints;

  /** Constructor. */
  KMeansClustering();

  /** Set the number of clusters to find. */
  void SetK(const unsigned int k);

  /** Get the number of clusters to find. */
  unsigned int GetK();

  /** Get the cluster centers.*/
  VectorOfPoints GetClusterCenters();

  std::vector<unsigned int> GetIndicesWithLabel(const unsigned int label);
  VectorOfPoints GetPointsWithLabel(const unsigned int label);

  /**
   * If this function is called, the randomness
   * is removed for repeatability for testing.
   */
  void SetRandom(const bool r);

  /** Set the points to cluster. */
  void SetPoints(const VectorOfPoints& points);

  std::vector<unsigned int> GetLabels();
  
  /** Set which initialization method to use. */
  void SetInitMethod(const int method);

  /** Choices of initialization methods */
  enum InitMethodEnum{RANDOM, KMEANSPP};

  /** Actually perform the clustering. */
  void Cluster();

  void OutputClusterCenters();
  
protected:

  /** Randomly initialize cluster centers */
  void RandomInit();

  /** Initialize cluster centers using the KMeans++ algorithm */
  void KMeansPPInit();

  /** Get the membership of 'queryPoint'. */
  unsigned int ClosestCluster(const PointType& queryPoint);

  /** Get the id of the closest point to 'queryPoint'. */
  unsigned int ClosestPointIndex(const PointType& queryPoint);

  /** Get the distance between 'queryPoint' and its closest point. */
  double ClosestPointDistance(const PointType& queryPoint);

  /** Get the distance between 'queryPoint' and its closest point excluding 'excludedId'. */
  double ClosestPointDistanceExcludingId(const PointType& queryPoint, const unsigned int excludedId);

  /** Get the distance between 'queryPoint' and its closest point excluding 'excludedIds'. */
  double ClosestPointDistanceExcludingIds(const PointType& queryPoint, const std::vector<unsigned int> excludedIds);

  /** Based on the current cluster membership, compute the cluster centers. */
  void EstimateClusterCenters();

  /** Construct an array of the closest cluster center to each point. */
  void AssignLabels();

  /** Determine if the membership of any point has changed. */
  bool CheckChanged(const std::vector<unsigned int> labels, const std::vector<unsigned int> oldLabels);

  /** Get a random point inside the bounding box of the points. */
  PointType GetRandomPointInBounds();

  /** Select a random index, with the probability of choosing an index weighted by the 'weights' vector. */
  unsigned int SelectWeightedIndex(const std::vector<double>& weights); // Intentionally not passed by reference

private:

  /** The label (cluster ID) of each point. */
  std::vector<unsigned int> Labels;

  /** Should the computation be random? If false, then it is repeatable (for testing). */
  bool Random;

  /** The initialization method to use */
  int InitMethod;

  /** The number of clusters to find */
  unsigned int K;
  
  /** The points to cluster. */
  VectorOfPoints Points;

  /** The current cluster centers. */
  VectorOfPoints ClusterCenters;
};

#endif
