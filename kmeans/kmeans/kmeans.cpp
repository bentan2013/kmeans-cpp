// kmeans.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdint.h>
#include <memory>
#include <math.h>
#include "kmeans_clustering.h"

const uint32_t num_lines = 161;

class point_feature
{
public:
  point_feature(uint32_t _id, double _xmin, double _ymin, double _xmax, double _ymax)
  {
    xmin = _xmin;
    ymin = _ymin;
    xmax = _xmax;
    ymax = _ymax;
    id = _id;
  }

  uint32_t id;
  double xmin;
  double ymin;
  double xmax;
  double ymax;
};

int main()
{
  FILE *f = nullptr;
  fopen_s(&f, "../../data/mbb.txt", "rt");
  if (f)
  {
    uint32_t id;
    double xmin, ymin, zmin, xmax, ymax, zmax;
    uint32_t a, b, c, d;

    std::shared_ptr<kmeans_clustering<point_feature*, 2>> sp_clustering = std::make_shared<kmeans_clustering<point_feature*, 2>>();
    std::vector<point_feature*> features;

    for (uint32_t line = 0; line < num_lines; line++)
    {
      fscanf_s(f, "%d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%d\t%d\t%d\t%d\n",
        &id,
        &xmin, &ymin, &zmin,
        &xmax, &ymax, &zmax,
        &a, &b, &c, &d);
      double pos[2];
      pos[0] = (xmin + xmax) / 2;
      pos[1] = (ymin + ymax) / 2;

      point_feature* p_feature = new point_feature(id, xmin, ymin, xmax, ymax);
      sp_clustering->insert_data(pos, p_feature);
    }

    uint32_t num_clusters = 20 > num_lines ? num_lines : 20;

    std::vector<kmeans_cluster<point_feature*,2>> clusters;
    sp_clustering->processing(num_clusters, clusters);

    for (std::vector<kmeans_cluster<point_feature*, 2>>::iterator iter = clusters.begin(); iter != clusters.end(); iter++)
    {
      uint32_t num_features = iter->get_data_count();
      for (uint32_t i = 0; i < num_clusters; i++)
      {
        point_feature* feature = nullptr;
        iter->get_data_at(i, feature);
        printf("id: %d\n", feature->id);
      }
    }
    fclose(f);
  }
  return 0;
}

