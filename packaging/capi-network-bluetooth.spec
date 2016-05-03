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
%if "%{?profile}" == "tv"
BuildRequires:  pkgconfig(bluetooth-api)
BuildRequires:  pkgconfig(db-util)
%else
BuildRequires:  pkgconfig(bluetooth-api)
%endif
BuildRequires:  pkgconfig(capi-base-common)
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

%package test
Summary: Network Bluetooth Framework test application
Group:   TO_BE/FILLED
Requires: %{name} = %{version}-%{release}

%description test
This package is C-API test application.

%prep
%setup -q
cp %{SOURCE1001} %{SOURCE1002} .

%build

%if "%{?_with_emulator}" == "1"
export CFLAGS="$CFLAGS -DTIZEN_BT_DISABLE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_BT_DISABLE"
export FFLAGS="$FFLAGS -DTIZEN_BT_DISABLE"

%if "%{?profile}" == "wearable"
export CFLAGS="$CFLAGS -DTIZEN_WEARABLE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_WEARABLE"
export FFLAGS="$FFLAGS -DTIZEN_WEARABLE"
%endif

%else # _with_emulator
export CFLAGS="$CFLAGS -DTIZEN_DEBUG_ENABLE -DTIZEN_ENGINEER_MODE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_DEBUG_ENABLE -DTIZEN_ENGINEER_MODE"
export FFLAGS="$FFLAGS -DTIZEN_DEBUG_ENABLE -DTIZEN_ENGINEER_MODE"

%if "%{?profile}" == "tv"
export CFLAGS="$CFLAGS -DTIZEN_OPP_CLIENT_DISABLE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_OPP_CLIENT_DISABLE"
export FFLAGS="$FFLAGS -DTIZEN_OPP_CLIENT_DISABLE"

export CFLAGS="$CFLAGS -DTIZEN_OPP_SERVER_DISABLE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_OPP_SERVER_DISABLE"
export FFLAGS="$FFLAGS -DTIZEN_OPP_SERVER_DISABLE"

export CFLAGS="$CFLAGS -DTIZEN_HFP_DISABLE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_HFP_DISABLE"
export FFLAGS="$FFLAGS -DTIZEN_HFP_DISABLE"
%endif


%if "%{?profile}" == "mobile" || "%{?profile}" == "common"
export CFLAGS="$CFLAGS -DBT_ENABLE_LEGACY_GATT_CLIENT"
export CXXFLAGS="$CXXFLAGS -DBT_ENABLE_LEGACY_GATT_CLIENT"
export FFLAGS="$FFLAGS -DBT_ENABLE_LEGACY_GATT_CLIENT"
%endif

export CFLAGS="$CFLAGS -DTIZEN_AUDIO_HF_DISABLE -DTIZEN_IPSP_SUPPORT"
export CXXFLAGS="$CXXFLAGS -DTIZEN_AUDIO_HF_DISABLE -DTIZEN_IPSP_SUPPORT"
export FFLAGS="$FFLAGS -DTIZEN_AUDIO_HF_DISABLE -DTIZEN_IPSP_SUPPORT"

%if "%{?profile}" == "wearable"
export CFLAGS="$CFLAGS -DTIZEN_HFP_DISABLE -DTELEPHONY_DISABLED -DTIZEN_HDP_DISABLE -DTIZEN_HID_HOST_DISABLE -DTIZEN_OPP_CLIENT_DISABLE -DTIZEN_OPP_SERVER_DISABLE -DTIZEN_WEARABLE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_HFP_DISABLE -DTELEPHONY_DISABLED -DTIZEN_HDP_DISABLE -DTIZEN_HID_HOST_DISABLE -DTIZEN_OPP_CLIENT_DISABLE -DTIZEN_OPP_SERVER_DISABLE -DTIZEN_WEARABLE"
export FFLAGS="$FFLAGS -DTIZEN_HFP_DISABLE -DTELEPHONY_DISABLED -DTIZEN_HDP_DISABLE -DTIZEN_HID_HOST_DISABLE -DTIZEN_OPP_CLIENT_DISABLE -DTIZEN_OPP_SERVER_DISABLE -DTIZEN_WEARABLE"
%endif
%endif # _with_emulator

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
%if "%{?profile}" == "wearable"
	-DTIZEN_WEARABLE=YES \
%else
%if "%{?profile}" == "tv"
	-DTIZEN_TV=YES \
%else
%if "%{?profile}" == "mobile"
	-DTIZEN_WEARABLE=NO \
%endif
%endif
%endif

MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER}

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install
install -D -m 0644 LICENSE %{buildroot}%{_datadir}/license/capi-network-bluetooth
install -D -m 0644 LICENSE %{buildroot}%{_datadir}/license/capi-network-bluetooth-devel


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%manifest %{name}.manifest
#%license LICENSE.APLv2 LICENSE
%{_libdir}/libcapi-network-bluetooth.so.*
%{_datadir}/license/capi-network-bluetooth
%{_datadir}/license/capi-network-bluetooth-devel

%files test
%manifest %{name}.manifest
%if "%{?profile}" != "tv"
%{_bindir}/bt_unit_test
%endif
#%{_bindir}/bt_onoff
#/etc/smack/accesses.d/capi-network-bluetooth-test.efl

%files devel
%manifest %{name}-devel.manifest
%{_includedir}/network/bluetooth.h
%{_includedir}/network/bluetooth_internal.h
%{_includedir}/network/bluetooth_type.h
%{_includedir}/network/bluetooth_type_internal.h
%{_includedir}/network/bluetooth_extension.h
%{_includedir}/network/bluetooth_type_extension.h

%{_libdir}/pkgconfig/capi-network-bluetooth.pc
%{_libdir}/libcapi-network-bluetooth.so

#%{_datadir}/license/capi-network-bluetooth-devel

