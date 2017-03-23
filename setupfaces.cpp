#include "setupfaces.h"
#include "facerecog.h"
setupfaces::setupfaces()
{

}
vector<Mat> setupfaces::preparefortraining()
{


    FaceRecog fr;
    vector<Mat> raw_faces;
    ofstream out_list(format("%s/%s", "output", "list").c_str());
    fr.readtraining(string("original/paths.txt"), raw_faces);
    int img_c = 0; //images counter
    int uselessint = 1;
    //now detect the faces in each of the raw images:
    for (vector<Mat>::const_iterator raw_img = raw_faces.begin() ; raw_img != raw_faces.end() ; raw_img++){
        vector<Rect> faces;
        //detect faces in the image
        fr.DetectFacesForCut(cascade,*raw_img, faces,uselessint);

        //cut each face and write to disk:
        for (vector<Rect>::const_iterator face = faces.begin() ; face != faces.end() ; face++){
            int edge_size = max(face->width, face->height);
            Rect square(face->x, face->y, edge_size, edge_size);
            Mat face_img = (*raw_img)(square);

            //resize:
            //face size = size(150,150)
           // resize(face_img, face_img, Size(150,150));

            //write to disk over here
            string face_path = format("%s/%d.jpg", "output", img_c++);
            imwrite(face_path,face_img);
            out_list << face_path << endl;

        }

    }
    out_list.close();
   return raw_faces;
}
