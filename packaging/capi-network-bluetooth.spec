Name:       capi-network-bluetooth
Summary:    Network Bluetooth Framework
Version: 0.1.2
Release:    1
Group:      TO_BE/FILLED_IN
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1001: packaging/capi-network-bluetooth.manifest 
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

BuildRequires:  pkgconfig(dbus-glib-1)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(bluetooth-api)
BuildRequires:  pkgconfig(capi-base-common)

BuildRequires:  cmake


%description
Network Bluetooth Framework

%package devel
Summary:    Network Bluetooth Framework (DEV)
Group:      TO_BE/FILLED
Requires:   %{name} = %{version}-%{release}

%description devel
Network Bluetooth Framework (DEV).

%prep
%setup -q

%build
cp %{SOURCE1001} .
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version} -DMAJORVER=${MAJORVER}

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%manifest capi-network-bluetooth.manifest
%{_libdir}/libcapi-network-bluetooth.so.*

%files devel
%manifest capi-network-bluetooth.manifest
%{_includedir}/network/bluetooth.h
%{_libdir}/pkgconfig/capi-network-bluetooth.pc
%{_libdir}/libcapi-network-bluetooth.so

