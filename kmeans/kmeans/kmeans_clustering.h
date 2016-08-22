#pragma once

#include <stdint.h>
#include <vector>

#define KMEANS_CLUSTER_QUAL kmeans_cluster<DATATYPE, NUMDIMS>


template<class DATATYPE, uint32_t NUMDIMS>
class kmeans_cluster
{
public:
  void get_center(double *pos, uint32_t & dims);
  void insert(const double pos[NUMDIMS], const DATATYPE & data);
  uint32_t get_data_count();
  void get_data_at(uint32_t id, DATATYPE & data);

protected:
  double center[NUMDIMS];
  std::vector<DATATYPE> data_array;
  std::vector<double> pos_array;
};

template<class DATATYPE, uint32_t NUMDIMS>
class kmeans_clustering
{
public:
  kmeans_clustering();
  virtual ~kmeans_clustering();

  //void add_data(const std::vector<double> pos_array[NUMDIMS], const std::vector<DATATYPE> & data_array);
  void insert_data(const double pos[NUMDIMS], const DATATYPE & data);
  void processing(uint32_t num_clusters, std::vector<KMEANS_CLUSTER_QUAL> & cluster_array);

};


/////////////////////////////////////////////////////////////////////////
template<class DATATYPE, uint32_t NUMDIMS>
void kmeans_cluster<DATATYPE, NUMDIMS>::get_center(double *pos, uint32_t & dims)
{

}

template<class DATATYPE, uint32_t NUMDIMS>
void kmeans_cluster<DATATYPE, NUMDIMS>::insert(const double pos[NUMDIMS], const DATATYPE & data)
{

}

template<class DATATYPE, uint32_t NUMDIMS>
uint32_t kmeans_cluster<DATATYPE, NUMDIMS>::get_data_count()
{
  return 0;
}

template<class DATATYPE, uint32_t NUMDIMS>
void kmeans_cluster<DATATYPE, NUMDIMS>::get_data_at(uint32_t id, DATATYPE & data)
{
}

//////////////////////////////////////////////////////////////////////////

template<class DATATYPE, uint32_t NUMDIMS>
kmeans_clustering<DATATYPE, NUMDIMS>::kmeans_clustering()
{
}


template<class DATATYPE, uint32_t NUMDIMS>
kmeans_clustering<DATATYPE, NUMDIMS>::~kmeans_clustering()
{
}

template<class DATATYPE, uint32_t NUMDIMS>
void kmeans_clustering<DATATYPE, NUMDIMS>::insert_data(const double pos[NUMDIMS], const DATATYPE & data)
{

}

template<class DATATYPE, uint32_t NUMDIMS>
void kmeans_clustering<DATATYPE, NUMDIMS>::processing(uint32_t num_clusters, std::vector<KMEANS_CLUSTER_QUAL> & cluster_array)
{

}
