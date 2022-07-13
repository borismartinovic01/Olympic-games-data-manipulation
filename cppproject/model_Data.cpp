#include "model_Data.h"
#include "Data.h"


std::string jstring2string(JNIEnv* env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray)env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t)env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char*)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

JNIEXPORT void JNICALL Java_model_Data_addDiscipline
(JNIEnv* env, jobject, jstring string1, jstring string2) {
    std::string disciplineName = jstring2string(env, string1);
    std::string type = jstring2string(env, string2);
    Data::getInstance()->addDiscipline(disciplineName, type);
}

JNIEXPORT void JNICALL Java_model_Data_addCountry
(JNIEnv* env, jobject, jstring string1) {
    std::string countryName = jstring2string(env, string1);
    Data::getInstance()->addCountry(countryName);
}

JNIEXPORT void JNICALL Java_model_Data_addGames
(JNIEnv* env, jobject, jstring string1, jstring string2) {
    std::string gamesName = jstring2string(env, string1);
    std::string city = jstring2string(env, string2);
    Data::getInstance()->addGames(gamesName, city);
}

JNIEXPORT void JNICALL Java_model_Data_addSport
(JNIEnv* env, jobject, jstring string1) {
    std::string sportName = jstring2string(env, string1);
    Data::getInstance()->addSport(sportName);
}

JNIEXPORT void JNICALL Java_model_Data_addMedal
(JNIEnv* env, jobject, jstring string1, jstring string2) {
    std::string type = jstring2string(env, string1);
    std::string gamesName = jstring2string(env, string2);
    Data::getInstance()->addMedal(type, gamesName);
}

JNIEXPORT jint JNICALL Java_model_Data_addTeam
(JNIEnv*, jobject) {
    return Data::getInstance()->addTeam();
}

JNIEXPORT void JNICALL Java_model_Data_addAthlete
(JNIEnv* env, jobject, jint int1, jstring string1, jstring string2, jint int2, jint int3, jint int4) {
    int id = (int)int1;
    std::string name = jstring2string(env, string1);
    std::string gender = jstring2string(env, string2);//ovo sad prosledi samo prvi karakter
    int age = (int)int2;
    int height = (int)int3;
    int weight = (int)int4;
    Data::getInstance()->addAthlete(id, name, gender[0], age, height, weight);
}

JNIEXPORT jint JNICALL Java_model_Data_countCompetitors
(JNIEnv* env, jobject, jstring string1, jstring string2, jstring string3, jstring string4, jstring string5) {
    std::string country = jstring2string(env, string1);
    std::string year = jstring2string(env, string2);
    std::string type = jstring2string(env, string3);
    std::string sport = jstring2string(env, string4);
    std::string medal = jstring2string(env, string5);
    return Data::getInstance()->countCompetitors(country, year, type, sport, medal);
}

JNIEXPORT void JNICALL Java_model_Data_addSportDiscipline
(JNIEnv* env, jobject, jstring string1, jstring string2) {
    std::string sport = jstring2string(env, string1);
    std::string discipline = jstring2string(env, string2);
    Data::getInstance()->getSport(sport)->second->addDiscipline(discipline);
}

JNIEXPORT void JNICALL Java_model_Data_addGamesCompetitor
(JNIEnv* env, jobject, jstring string1, jint int1) {
    std::string games = jstring2string(env, string1);
    int id = (int)int1;
    Data::getInstance()->getGames(games)->second->addCompetitor(id);
}

JNIEXPORT void JNICALL Java_model_Data_addCountryCompetitor
(JNIEnv* env, jobject, jstring string1, jint int1) {
    std::string country = jstring2string(env, string1);
    int id = (int)int1;
    Data::getInstance()->getCountry(country)->second->addCompetitor(id);
}

JNIEXPORT void JNICALL Java_model_Data_addCompetitorMedals
(JNIEnv* env, jobject, jint int1, jstring string1, jstring string2) {
    int competitorId = (int)int1;
    std::string discipline = jstring2string(env, string1);
    std::string gamesMedal = jstring2string(env, string2);

    auto it = Data::getInstance()->getCompetitor(competitorId);
    Competitor* comp = it->second;

    comp->addMedals(std::initializer_list<std::pair<string, string> >{make_pair(discipline, gamesMedal)});
    
}

JNIEXPORT void JNICALL Java_model_Data_addCompetitorDiscipline
(JNIEnv* env, jobject, jint int1, jstring string1, jstring string2) {
    int competitorId = (int)int1;
    std::string games = jstring2string(env, string1);
    std::string discipline = jstring2string(env, string2);

    auto it = Data::getInstance()->getCompetitor(competitorId);
    Competitor* comp = it->second;

    comp->addDiscipline(std::initializer_list<std::pair<string, string> >{make_pair(games, discipline)});
}

JNIEXPORT void JNICALL Java_model_Data_addCompetitorCountry
(JNIEnv* env, jobject, jint int1, jstring string1, jstring string2) {
    int competitorId = (int)int1;
    std::string country = jstring2string(env, string1);
    std::string gamesMedal = jstring2string(env, string2);

    auto it = Data::getInstance()->getCompetitor(competitorId);
    Competitor* comp = it->second;

    comp->addCountry(std::initializer_list<std::pair<string, string> >{make_pair(country, gamesMedal)});
}

JNIEXPORT void JNICALL Java_model_Data_addTeamAthlete
(JNIEnv*, jobject, jint int1, jint int2) {
    int teamId = (int)int1;
    int athleteId = (int)int2;

    auto it = Data::getInstance()->getCompetitor(teamId);
    Team* team = (Team*)(it->second);

    team->addAthlete(athleteId);
}

JNIEXPORT void JNICALL Java_model_Data_deleteData
(JNIEnv*, jobject) {
    delete Data::getInstance();
}

JNIEXPORT jint JNICALL Java_model_Data_numofDisciplines
(JNIEnv* env, jobject, jstring string1) {
    std::string yearSeason = jstring2string(env, string1);
    return Data::getInstance()->numofDisciplines(yearSeason);
}

JNIEXPORT jdouble JNICALL Java_model_Data_avgHeight
(JNIEnv* env, jobject, jstring string1) {
    std::string yearSeason = jstring2string(env, string1);
    return Data::getInstance()->avgHeight(yearSeason);
}

JNIEXPORT jdouble JNICALL Java_model_Data_avgWeight
(JNIEnv* env, jobject, jstring string1) {
    std::string yearSeason = jstring2string(env, string1);
    return Data::getInstance()->avgWeight(yearSeason);
}