#pragma once

#include <stdint.h>
#include <vector>
#include <time.h>

#define KMEANS_CLUSTER_EXP kmeans_cluster<DATATYPE, NUMDIMS>
#define KMEANS_CLUSTERING_EXP kmeans_clustering<DATATYPE, NUMDIMS>

#define KMEANS_TEMPLATE template<class DATATYPE, uint32_t NUMDIMS>

#define POS_TEMPLATE template<uint32_t NUMDIMS>
#define POS_EXP position<NUMDIMS>


POS_TEMPLATE
class position
{
public:
  position() { ; }
  position(double *p, uint32_t dims = NUMDIMS);
    ~ position() { ; }
public:
  double pos[NUMDIMS];
};

POS_TEMPLATE
POS_EXP::position(double *p, uint32_t dims = NUMDIMS)
{
  for (uint32_t i = 0; i < dims; i++)
  {
    pos[i] = p[i];
  }
}

////////////////////////////////////////////

KMEANS_TEMPLATE
class kmeans_cluster
{
public:
  kmeans_cluster() { ; }
  ~kmeans_cluster() { ; }
  POS_EXP get_center();
  void insert(const double pos[NUMDIMS], const DATATYPE & data);
  uint32_t get_data_count();
  bool get_data_at(uint32_t id, DATATYPE & data);
  uint32_t get_id();

protected:
  POS_EXP center;
  uint32_t id;

  std::vector<DATATYPE> data_array;
  std::vector<POS_EXP> pos_array;
};


/////////////////////////////////////////////////////////////////////////

KMEANS_TEMPLATE
uint32_t KMEANS_CLUSTER_EXP::get_id()
{
  return id;
}

KMEANS_TEMPLATE
POS_EXP KMEANS_CLUSTER_EXP::get_center()
{

}

KMEANS_TEMPLATE
void KMEANS_CLUSTER_EXP::insert(const double pos[NUMDIMS], const DATATYPE & data)
{
  pos_array.push_back(pos);
  data_array.push_back(data);
}

KMEANS_TEMPLATE
uint32_t KMEANS_CLUSTER_EXP::get_data_count()
{
  return (uint32_t)data_array.size();
}

KMEANS_TEMPLATE
bool KMEANS_CLUSTER_EXP::get_data_at(uint32_t id, DATATYPE & data)
{
  if (id < get_data_count())
  {
    data = data_array[id];
    return true;
  }

  return false;
}

KMEANS_TEMPLATE
class kmeans_clustering
{
public:
  kmeans_clustering();
  virtual ~kmeans_clustering();

  //void add_data(const std::vector<double> pos_array[NUMDIMS], const std::vector<DATATYPE> & data_array);
  void insert_data(const double pos[NUMDIMS], const DATATYPE & data);
  void processing(uint32_t num_clusters, std::vector<KMEANS_CLUSTER_EXP> & cluster_array);
  double dist(double* p1, double *p2, uint32_t dims = NUMDIMS);

protected:
  std::vector<double[NUMDIMS]> pos_array;
  std::vector<DATATYPE> data_array;
};



//////////////////////////////////////////////////////////////////////////
KMEANS_TEMPLATE
double KMEANS_CLUSTERING_EXP::dist(double* p1, double *p2, uint32_t dims)
{
  double val = 0;
  for (uint32_t i = 0; i < dims; i++)
  {
    val += fabs(p1[i] - p2[i]);
  }
  return val;
}


KMEANS_TEMPLATE
KMEANS_CLUSTERING_EXP::kmeans_clustering()
{
}


KMEANS_TEMPLATE
KMEANS_CLUSTERING_EXP::~kmeans_clustering()
{
}

KMEANS_TEMPLATE
void KMEANS_CLUSTERING_EXP::insert_data(const double pos[NUMDIMS], const DATATYPE & data)
{
}

KMEANS_TEMPLATE
void KMEANS_CLUSTERING_EXP::processing(uint32_t num_clusters, std::vector<KMEANS_CLUSTER_EXP> & cluster_array)
{
  // init k clusters
  cluster_array.resize(num_clusters);
  srand((unsigned int)time(nullptr));
  for (uint32_t k = 0; k < num_clusters; k++)
  {


  }

}
