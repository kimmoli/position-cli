Name:       position

%{!?qtc_qmake:%define qtc_qmake %qmake}
%{!?qtc_qmake5:%define qtc_qmake5 %qmake5}
%{!?qtc_make:%define qtc_make make}
%{?qtc_builddir:%define _builddir %qtc_builddir}
Summary:    Command line position
Version:    0.0.1
Release:    1
Group:      Qt/Qt
License:    LICENSE
URL:
Source0:    %{name}-%{version}.tar.bz2

BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Positioning)

%description
Command line tool for getting lat/long position


%prep
%setup -q -n %{name}-%{version}


%build

%qtc_qmake5 SPECVERSION=%{version}

%qtc_make %{?_smp_mflags}


%install
rm -rf %{buildroot}

%qmake5_install

%files
%defattr(-,root,root,-)
%{_bindir}
