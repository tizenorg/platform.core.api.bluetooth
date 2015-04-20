Name:       capi-network-bluetooth
Summary:    Network Bluetooth Framework
Version:    0.1.52
Release:    1
Group:      Connectivity/API
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1001:	%{name}.manifest
Source1002:	%{name}-devel.manifest
#Requires(post): /sbin/ldconfig
#Requires(postun): /sbin/ldconfig

BuildRequires:  pkgconfig(dbus-glib-1)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(bluetooth-api)
BuildRequires:  pkgconfig(capi-base-common)
%if "%{?tizen_profile_name}" == "wearable"
BuildRequires:  pkgconfig(privacy-manager-client)
%endif

BuildRequires:  cmake


%description
Network Bluetooth Framework

%package devel
Summary:    Network Bluetooth Framework (DEV)
Group:      Development/Connectivit
Requires:   %{name} = %{version}-%{release}

%description devel
Network Bluetooth Framework.

%devel_desc

%prep
%setup -q
cp %{SOURCE1001} %{SOURCE1002} .

%build
%if "%{?tizen_profile_name}" == "wearable"
export CFLAGS="$CFLAGS -DTIZEN_WEARABLE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_WEARABLE"
export FFLAGS="$FFLAGS -DTIZEN_WEARABLE"
%endif

export CFLAGS="$CFLAGS -DTIZEN_DEBUG_ENABLE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_DEBUG_ENABLE"
export FFLAGS="$FFLAGS -DTIZEN_DEBUG_ENABLE"

export CFLAGS="$CFLAGS -DTIZEN_ENGINEER_MODE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_ENGINEER_MODE"
export FFLAGS="$FFLAGS -DTIZEN_ENGINEER_MODE"

%if "%{?tizen_profile_name}" == "wearable"
export CFLAGS+=" -DTELEPHONY_DISABLED"
export CXXFLAGS+=" -DTELEPHONY_DISABLED"
export FFLAGS+=" -DTELEPHONY_DISABLED"
%endif

%ifarch aarch64
echo arch64
export CFLAGS+=" -DARCH64"
export CXXFLAGS+=" -DARCH64"
export FFLAGS+=" -DARCH64"
%endif

%ifarch x86_64
echo x86_64
export CFLAGS+=" -DARCH64"
export CXXFLAGS+=" -DARCH64"
export FFLAGS+=" -DARCH64"
%endif

%cmake \
%if "%{?tizen_profile_name}" == "wearable"
	-DTIZEN_WEARABLE=YES \
%else
%if "%{?tizen_profile_name}" == "mobile"
	-DTIZEN_WEARABLE=NO \
%endif
%endif

MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER}

make %{?jobs:-j%jobs}

%install
%make_install


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%manifest %{name}.manifest
%license LICENSE.APLv2 LICENSE
%{_libdir}/libcapi-network-bluetooth.so.*
#%{_datadir}/license/capi-network-bluetooth

#%files test
#%manifest bluetooth-test.manifest
#%{_bindir}/bt_unit_test
#%{_bindir}/bt_onoff
#/etc/smack/accesses.d/capi-network-bluetooth-test.efl

%files devel
%manifest %{name}-devel.manifest
%{_includedir}/network/bluetooth.h
%{_includedir}/network/bluetooth_type.h
%{_libdir}/pkgconfig/capi-network-bluetooth.pc
%{_libdir}/libcapi-network-bluetooth.so
#%{_datadir}/license/capi-network-bluetooth-devel

