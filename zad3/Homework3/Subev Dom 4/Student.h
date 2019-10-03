#pragma once
struct Student
{
	long int FN;
	char firstName[14];
	char secondName[14];
	Student()
	{
		FN = 00000;
		firstName[0] = '\0';
		secondName[0] = '\0';
	}
};
ostream& operator<<(ostream& os,const Student& st)
{
	os << st.FN;
	return os;
}
bool operator<(const Student& lfs,const Student& rfs)
{
	return lfs.FN < rfs.FN;
}
bool operator>(const Student& lfs,const Student& rfs)
{
	return lfs.FN > rfs.FN;
}
bool operator==(const Student& lfs,const Student& rfs)
{
	return lfs.FN == rfs.FN;
}