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
  position()
  {
    for (uint32_t i = 0; i < NUMDIMS; i++)
    {
      pos[i] = 0.0;
    }
  }

  static double dist(const POS_EXP & pos1, const POS_EXP & pos2);
  static double square_dist(const POS_EXP & pos1, const POS_EXP & pos2);
  void init(double *p, uint32_t dims = NUMDIMS);
    ~ position() { ; }
public:
  double pos[NUMDIMS];
};

POS_TEMPLATE
double POS_EXP::dist(const POS_EXP & p1, const POS_EXP & p2)
{
  double val = 0;
  for (uint32_t i = 0; i < NUMDIMS; i++)
  {
    val += (p1.pos[i] - p2.pos[i]) * (p1.pos[i] - p2.pos[i]);
  }
  return sqrt(val);
}

POS_TEMPLATE
double POS_EXP::square_dist(const POS_EXP & p1, const POS_EXP & p2)
{
  double val = 0;
  for (uint32_t i = 0; i < NUMDIMS; i++)
  {
    val += (p1.pos[i] - p2.pos[i]) * (p1.pos[i] - p2.pos[i]);
  }
  return val;
}

POS_TEMPLATE
void POS_EXP::init(double *p, uint32_t dims = NUMDIMS)
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
  void calculate_center();
  void clear();
  double square_error();
  void insert(const POS_EXP & pos, const DATATYPE & data);
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
double KMEANS_CLUSTER_EXP::square_error()
{
  double val = 0.0;
  for (std::vector<POS_EXP>::iterator iter = pos_array.begin(); iter != pos_array.end(); iter++)
  {
    val += POS_EXP::square_dist(center, (*iter));
  }
  return val;
}

KMEANS_TEMPLATE
void KMEANS_CLUSTER_EXP::clear()
{
  data_array.clear();
  pos_array.clear();
}

KMEANS_TEMPLATE
uint32_t KMEANS_CLUSTER_EXP::get_id()
{
  return id;
}

KMEANS_TEMPLATE
POS_EXP KMEANS_CLUSTER_EXP::get_center()
{
	return center;
}

KMEANS_TEMPLATE
void KMEANS_CLUSTER_EXP::calculate_center()
{
  POS_EXP _center;
  for (std::vector<POS_EXP>::iterator iter = pos_array.begin(); iter != pos_array.end(); iter++)
  {
    for (uint32_t i = 0; i < NUMDIMS; i++)
    {
      _center.pos[i] += (*iter).pos[i];
    }
  }

  for (uint32_t i = 0; i < NUMDIMS; i++)
  {
    _center.pos[i] /= pos_array.size();
    center = _center;
  }
}

KMEANS_TEMPLATE
void KMEANS_CLUSTER_EXP::insert(const POS_EXP & pos, const DATATYPE & data)
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
  kmeans_clustering() { ; }
  virtual ~kmeans_clustering() { ; }

  //void add_data(const std::vector<double> pos_array[NUMDIMS], const std::vector<DATATYPE> & data_array);
  void insert_data(const double pos[NUMDIMS], const DATATYPE & data);
  void processing(uint32_t num_clusters, double tolerance, uint32_t max_iter, std::vector<KMEANS_CLUSTER_EXP> & cluster_array);

protected:
  uint32_t select_cluster(const POS_EXP & pos, std::vector<KMEANS_CLUSTER_EXP> & cluster_array);

protected:
  std::vector<POS_EXP> pos_array;
  std::vector<DATATYPE> data_array;
};



//////////////////////////////////////////////////////////////////////////

KMEANS_TEMPLATE
uint32_t KMEANS_CLUSTERING_EXP::select_cluster(const POS_EXP & pos, std::vector<KMEANS_CLUSTER_EXP> & cluster_array)
{
  double min = FLT_MAX;
  uint32_t id = 0;
  uint32_t num_clusters = cluster_array.size();
  for (uint32_t i = 0; i < num_clusters; i++)
  {
    double current_dist = POS_EXP::dist(pos, cluster_array[i].get_center());
    if (current_dist < min)
    {
      id = i;
      min = current_dist;
    }
  }

  return id;
}

KMEANS_TEMPLATE
void KMEANS_CLUSTERING_EXP::insert_data(const double pos[NUMDIMS], const DATATYPE & data)
{
  POS_EXP position;
  position.init((double*)pos, NUMDIMS);
  pos_array.push_back(position);
  data_array.push_back(data);
}

KMEANS_TEMPLATE
void KMEANS_CLUSTERING_EXP::processing(uint32_t num_clusters, double tolerance, uint32_t max_iter, std::vector<KMEANS_CLUSTER_EXP> & cluster_array)
{
  uint32_t feature_count = data_array.size();

  // init k clusters
  cluster_array.resize(num_clusters);
  srand((unsigned int)time(nullptr));
  for (uint32_t k = 0; k < num_clusters; k++)
  {
    int id = rand() % feature_count;
    cluster_array[k].insert(pos_array[id], data_array[id]);
    cluster_array[k].calculate_center();
  }

  double old_val = 0.0;
  double new_val = tolerance * 2;
  uint32_t num_iter = 0;
  while ( fabs(old_val - new_val) > tolerance || num_iter < max_iter)
  {
    old_val = new_val;
    for (uint32_t k = 0; k < num_clusters; k++)
    {
      cluster_array[k].clear();
    }

    for (uint32_t i = 0; i < feature_count; i++)
    {
      uint32_t cluster_id = select_cluster(pos_array[i], cluster_array);
      cluster_array[cluster_id].insert(pos_array[i], data_array[i]);
    }

    double total_val = 0.0;
    for (uint32_t k = 0; k < num_clusters; k++)
    {
      cluster_array[k].calculate_center();
      total_val += cluster_array[k].square_error();
    }
    new_val = total_val;
	num_iter++;
  }

  







}
