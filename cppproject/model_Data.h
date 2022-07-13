/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class model_Data */

#ifndef _Included_model_Data
#define _Included_model_Data
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     model_Data
 * Method:    addDiscipline
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_model_Data_addDiscipline
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     model_Data
 * Method:    addCountry
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_model_Data_addCountry
  (JNIEnv *, jobject, jstring);

/*
 * Class:     model_Data
 * Method:    addGames
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_model_Data_addGames
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     model_Data
 * Method:    addSport
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_model_Data_addSport
  (JNIEnv *, jobject, jstring);

/*
 * Class:     model_Data
 * Method:    addMedal
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_model_Data_addMedal
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     model_Data
 * Method:    addTeam
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_model_Data_addTeam
  (JNIEnv *, jobject);

/*
 * Class:     model_Data
 * Method:    addAthlete
 * Signature: (ILjava/lang/String;Ljava/lang/String;III)V
 */
JNIEXPORT void JNICALL Java_model_Data_addAthlete
  (JNIEnv *, jobject, jint, jstring, jstring, jint, jint, jint);

/*
 * Class:     model_Data
 * Method:    countCompetitors
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_model_Data_countCompetitors
  (JNIEnv *, jobject, jstring, jstring, jstring, jstring, jstring);

/*
 * Class:     model_Data
 * Method:    addSportDiscipline
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_model_Data_addSportDiscipline
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     model_Data
 * Method:    addGamesCompetitor
 * Signature: (Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_model_Data_addGamesCompetitor
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     model_Data
 * Method:    addCountryCompetitor
 * Signature: (Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_model_Data_addCountryCompetitor
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     model_Data
 * Method:    addCompetitorMedals
 * Signature: (ILjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_model_Data_addCompetitorMedals
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     model_Data
 * Method:    addCompetitorDiscipline
 * Signature: (ILjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_model_Data_addCompetitorDiscipline
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     model_Data
 * Method:    addCompetitorCountry
 * Signature: (ILjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_model_Data_addCompetitorCountry
  (JNIEnv *, jobject, jint, jstring, jstring);

/*
 * Class:     model_Data
 * Method:    addTeamAthlete
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_model_Data_addTeamAthlete
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     model_Data
 * Method:    deleteData
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_model_Data_deleteData
  (JNIEnv *, jobject);

/*
 * Class:     model_Data
 * Method:    numofDisciplines
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_model_Data_numofDisciplines
  (JNIEnv *, jobject, jstring);

/*
 * Class:     model_Data
 * Method:    avgHeight
 * Signature: (Ljava/lang/String;)D
 */
JNIEXPORT jdouble JNICALL Java_model_Data_avgHeight
  (JNIEnv *, jobject, jstring);

/*
 * Class:     model_Data
 * Method:    avgWeight
 * Signature: (Ljava/lang/String;)D
 */
JNIEXPORT jdouble JNICALL Java_model_Data_avgWeight
  (JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif